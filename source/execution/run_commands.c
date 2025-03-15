/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/05 17:44:06 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_command_parameters(t_shell *data, t_cmd *command)
{
	while (command)
	{
		if (command->input_expanded)
			free_pointers(1, &command->input_expanded);
		if (command->args)
		{
			free_split(command->args);
			command->args = NULL;
		}
		if (command->path)
			free_pointers(1, &command->path);
		prepare_parameters(command, data);
		command = command->next;
	}
}

static bool	is_safe_to_run_builtin(t_cmd *command)
{
	bool	cond_1;
	bool	cond_2;

	cond_1 = (command->delimiter == AND_DOUBLE
			|| command->delimiter == PIPE_DOUBLE
			|| command->delimiter == NO_TOKEN);
	cond_2 = command->settings.is_builtin;
	if (command->settings.builtin_id == ECHO)
	{
		command->settings.istb = true;
		return (false);
	}
	if (cond_1 && cond_2)
	{
		command->settings.iste = false;
		command->settings.istb = false;
		return (true);
	}
	if (command->delimiter == PIPE_SINGLE)
		command->settings.istb = true;
	return (false);
}

bool	run_builting_separately(t_shell *data, t_cmd *command)
{
	if (is_safe_to_run_builtin(command))
	{
		if (process_builtin(data, command, STDOUT_FILENO) < 0)
			handle_error(E_MALLOC, NULL, __func__);
		if (command->settings.builtin_id == EXPORT)
			refresh_command_parameters(data, command->next);
		return (true);
	}
	return (false);
}

static void	execute_cmd(t_shell *data, t_cmd *command)
{
	if (run_eof(data, command))
		return ;
	while (command)
	{
		signal(SIGINT, SIG_IGN);
		run_builting_separately(data, command);
		if (command->delimiter != AND_DOUBLE && command->next
			&& pipe(data->pipe_id) == -1)
			return ((void)handle_error(E_PF, NULL, __func__));
		if (do_fork(&data->pid))
			return ((void)handle_error(E_PF, NULL, __func__));
		else if (data->pid == 0)
			child_process(data, command);
		else if (data->pid != 0)
		{
			if (parent_process(data, &command))
				break ;
			command = command->next;
		}
	}
	return ;
}

void	run_commands(t_shell *data)
{
	data->prev_fd = -1;
	ft_memset(data->pipe_id, -1, sizeof(int) * 2);
	execute_cmd(data, data->command);
	set_last_status(data);
}

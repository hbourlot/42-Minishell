/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 15:42:57 by joralves         ###   ########.fr       */
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

static bool	is_safe_to_run_builtin(t_shell *data, t_cmd *command)
{
	bool	cond_1;
	bool	cond_2;
	bool	cond_3;

	cond_1 = (command->delimiter == AND_DOUBLE
			|| command->delimiter == PIPE_DOUBLE
			|| command->delimiter == NO_TOKEN);
	cond_2 = command->settings.is_builtin;
	cond_3 = command->rf;
	if (cond_1 && cond_2)
	{
		command->settings.is_safe_to_execve = false;
		if (command->settings.builtin_id == ECHO)
		{
			command->settings.is_safe_to_builtin = true;
			return (false);
		}
		command->settings.is_safe_to_builtin = false;
		return (true);
	}
	return (false);
}

bool	run_builting_separately(t_shell *data, t_cmd *command)
{
	if (is_safe_to_run_builtin(data, command))
	{
		if (process_builtin(data, command) < 0)
			handle_error(E_MALLOC, NULL, __func__);
		if (command->settings.builtin_id == EXPORT)
			refresh_command_parameters(data, command->next);
		return (true);
	}
	return (false);
}

int	command_loop(t_shell *data, t_cmd *command)
{
	signal(SIGINT, SIG_IGN);
	while (command)
	{
		run_builting_separately(data, command);
		if (command->delimiter != AND_DOUBLE && command->next
			&& pipe(data->pipe_id) == -1)
			return (handle_error(E_EOF, NULL, __func__), -1);
		if (do_fork(&data->pid))
			return (handle_error(E_EOF, NULL, __func__), -1);
		else if (data->pid == 0)
		{
			restore_signals();
			child_process(data, command);
		}
		else
		{
			if (parent_process(data, &command))
				break ;
			command = command->next;
		}
	}
	return (0);
}

void	run_commands(t_shell *data)
{
	int	wait_status;

	data->prev_fd = -1;
	ft_memset(data->pipe_id, -1, sizeof(int) * 2);
	if ((data->eof))
	{
		if (run_eof(data, &data->pid))
			return ;
		set_last_status(data);
		if (data->exit_status == 130 || data->exit_status == 131)
			return ;
	}
	command_loop(data, data->command);
	set_last_status(data);
}

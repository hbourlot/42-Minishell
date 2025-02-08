/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/08 17:26:34 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_safe_to_run_builtin(t_shell *data, t_cmd *command)
{
	bool	cond_1;
	bool	cond_2;
	bool	cond_3;

	cond_1 = (command->delimiter == AND_DOUBLE
			|| command->delimiter == PIPE_DOUBLE || command->delimiter == NO_TOKEN);
	cond_2 = command->settings.is_builtin;
	cond_3 = command->redir_files;
	if (cond_1 && cond_2)
	{
		command->settings.is_safe_to_execve = false;
		if (command->settings.builtin_id == ECHO)
		{
			command->settings.is_safe_to_builtin = true;
			return false;
		}
		command->settings.is_safe_to_builtin = false;
		return true;
	}
	return (false);
}

bool	run_builting_separately(t_shell *data, t_cmd *command)
{
	if (is_safe_to_run_builtin(data, command))
	{
		if (process_builtin(data, command) < 0)
		{
			set_error_ex(1, "Malloc", NULL, true);
			handle_error();
		}
		return (true);
	}
	return (false);
}

void	command_loop(t_shell *data, t_cmd *command)
{
	signal(SIGINT, SIG_IGN);
	while (command)
	{
		run_builting_separately(data, command);
		if (command->delimiter != AND_DOUBLE && command->next
			&& pipe(data->pipe_id) == -1)
			return (set_error_ex(1, "Pipe", NULL, false));
		if (do_fork(&data->pid))
			return (set_error_ex(1, "Fork", NULL, false));
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
	// print_error_information(data);
}

void	run_commands(t_shell *data)
{
	int	wait_status;

	data->prev_fd = -1;
	ft_memset(data->pipe_id, -1, sizeof(int) * 2);
	if ((data->eof))
	{
		if (run_eof(data, &data->pid))
		{
			data->exit_status = 1;
			return ;
		}
		set_last_status(data);
		if (data->exit_status == 130 || data->exit_status == 131)
			return ;
	}
	command_loop(data, data->command);
	set_last_status(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 18:10:44 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *command)
{
	bool	*builtin_flags[] = {&command->settings.builtin_cd,
			&command->settings.builtin_export, &command->settings.builtin_echo,
			&command->settings.builtin_env, &command->settings.builtin_unset,
			&command->settings.builtin_exit, &command->settings.builtin_pwd,
			NULL};
	int		i;

	i = 0;
	while (builtin_flags[i])
	{
		if (*builtin_flags[i])
			return (true);
		i++;
	}
	return (false);
}

void	command_loop(t_shell *data, t_cmd *command)
{
	signal(SIGINT, SIG_IGN);
	while (command)
	{
		if (is_builtin(command) && !command->next && !command->redir_files)
		{
			if (process_builtin(data, command) < 0)
			{
				set_error_execution(1, "Malloc", NULL, true);
				handle_error();
			}
			return ;
		}
		if (command->delimiter != AND_DOUBLE && command->next
			&& pipe(data->pipe_id) == -1)
			return (set_error_execution(1, "Pipe", NULL, false));
		if (do_fork(&data->pid))
			return (set_error_execution(1, "Fork", NULL, false));
		else if (data->pid == 0)
		{
			restore_signals();
			child_process(data, command, data->pipe_id, &data->prev_fd);
		}
		else
		{
			if (parent_process(data, command))
				break ;
			command = command->next;
		}
	}
}

void	run_commands(t_shell *data)
{
	data->prev_fd = -1;
	ft_memset(data->pipe_id, -1, sizeof(int) * 2);
	if ((data->eof))
		run_eof(data, data->pipe_id, &data->prev_fd, &data->pid);
	command_loop(data, data->command);
	if (data->last_cmd_executed
		&& data->last_cmd_executed->delimiter == PIPE_DOUBLE)
	{
		if (handle_double_pipe(data))
			return ;
	}
	else if (data->last_cmd_executed
		&& data->last_cmd_executed->delimiter == AND_DOUBLE)
	{
		handle_double_and(data, data->last_cmd_executed);
	}
	set_last_status(data);
}

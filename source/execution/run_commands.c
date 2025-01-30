/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/30 15:36:40 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parent_process(t_shell *data, t_cmd *command, int *pipe_id, int *prev_fd)
{

	data->commands_ran += 1;
	data->last_cmd_executed = command;
	if (command->next)
		close(pipe_id[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (command->next)
		*prev_fd = pipe_id[0];
	if (command->delimiter == PIPE_DOUBLE)
		return (1);
	if (command->delimiter == AND_DOUBLE)
		handle_double_and(data, command);
	return (0);
}

/*
 * Need to see how to capture the pid to send properly to the main run shell
 */
static void	command_loop(t_shell *data, t_cmd *command, pid_t *pid)
{
	if ((data->eof))
		run_eof(data, data->pipe_id, &data->prev_fd, pid);
	while (command)
	{
		// * Probably handle builting here
		if (command->next && pipe(data->pipe_id) == -1)
			return (set_error_execution(1, "Pipe", NULL, false));
		if (do_fork(pid))
			return (set_error_execution(1, "Fork", NULL, false));
		else if (*pid == 0)
			child_process(data, command, data->pipe_id, &data->prev_fd);
		else
		{
			if (parent_process(data, command, data->pipe_id, &data->prev_fd))
				break;
			command = command->next;
		}
	}
}

static void	set_last_status(t_shell *data, pid_t *pid)
{
	int		status;
	int		wait_status;
	pid_t	prev_pid;
	int		i;

	i = 0;
	prev_pid = 0;	
	while (i < data->commands_ran)
	{
		*pid = waitpid(-1, &wait_status, 0);
		if (WIFEXITED(wait_status) && *pid > prev_pid)
			status = WEXITSTATUS(wait_status);
		prev_pid = *pid;
		i++;
	}
	data->exit_status = status;
}

void	run_commands(t_shell *data)
{
	pid_t	pid;

	data->prev_fd = -1;
	ft_memset(data->pipe_id, -1, sizeof(int) * 2);
	command_loop(data, data->command, &data->pid);
	while (data->nbr_of_commands != data->commands_ran)
	{
		set_last_status(data, &pid);
		if (data->exit_status == 0)
		{
			if (print_command_on_terminal(data, &data->pid) < 0)
			{
				set_error_execution(1, "Read", NULL, 0);
				handle_error();
			}
			return;
		}
		command_loop(data, data->last_cmd_executed->next, &pid);
	}
	set_last_status(data, &pid);
}

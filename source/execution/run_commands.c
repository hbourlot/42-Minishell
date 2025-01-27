/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/23 01:11:28 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * I need to make some logic of error so i send the properly print message
 * and the properly error number but dont exit since the program needs to
 * keep working
 */
void	close_resources(int exit_code, int *pipe_id, char *msg)
{
	if (pipe_id[0] != 1)
		close(pipe_id[0]);
	if (pipe_id[1] != -1)
		close(pipe_id[1]);
	perror(msg);
	exit(exit_code);
}

static int	parent_process(t_shell *data, t_cmd *command, int *pipe_id,
		int *prev_fd)
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
	return (0);
}

/*
 * Need to see how to capture the pid to send properly to the main run shell
 */
static void	command_loop(t_shell *data, t_cmd *command, pid_t *pid)
{
	int	pipe_id[2];
	int	prev_fd;

	prev_fd = -1;
	ft_memset(pipe_id, -1, sizeof(int) * 2);
	if ((data->eof))
		run_eof(data, pipe_id, &prev_fd, pid);
	while (command)
	{
		// * Probably handle builting here
		if (command->next && pipe(pipe_id) == -1)
			return (set_error_execution(1, "Pipe", NULL, false));
		*pid = fork();
		if (*pid < 0)
			return (set_error_execution(1, "Fork", NULL, false));
		else if (*pid == 0)
			child_process(data, command, pipe_id, &prev_fd);
		else
		{
			if (parent_process(data, command, pipe_id, &prev_fd))
				break ;
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

	command_loop(data, data->command, &pid);
	while (data->nbr_of_commands != data->commands_ran)
	{
		set_last_status(data, &pid);
		if (data->exit_status == 0)
			return ;
		command_loop(data, data->last_cmd_executed->next, &pid);
	}
	set_last_status(data, &pid);
}

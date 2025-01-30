/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/28 23:59:24 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* 
	* Need to see how to capture the pid to send properly to the main run shell
*/
void	command_loop(t_shell *data, t_cmd *command)
{
	while (command)
	{
		// * Probably handle builting here
		if (command->delimiter != AND_DOUBLE && command->next && pipe(data->pipe_id) == -1)
			return (set_error_execution(1, "Pipe", NULL, false));
		if (do_fork(&data->pid))
			return (set_error_execution(1, "Fork", NULL, false));
		else if (data->pid == 0)
		{
			child_process(data, command, data->pipe_id, &data->prev_fd);
		}
		else
		{
			if (parent_process(data, command))
				break;
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

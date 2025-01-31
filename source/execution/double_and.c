/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:05:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/28 23:57:40 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	there_is_double_pipe(t_shell *data)
{
	t_cmd *current;

	current = NULL;
	if (data->last_cmd_executed)
		current = data->last_cmd_executed;
	else
		current = data->command;
	while (current)
	{
		if (current->delimiter == PIPE_DOUBLE)
		{
			data->last_cmd_executed = current;
			return (0);
		}
		current = current->next;
	}
	return 1;
}

void	handle_double_and(t_shell *data, t_cmd *command)
{
	set_last_status(data);
	if (data->exit_status != 0 && there_is_double_pipe(data))
			return ;
	if (do_fork(&data->pid))
		return ;
	else if (data->pid == 0)
		child_process(data, command->next, data->pipe_id, &data->prev_fd);
	else
	{
        data->commands_ran += 1;
        data->last_cmd_executed = command;
			set_last_status(data);
		if (data->exit_status != 0)
		{
			if (there_is_double_pipe(data))
				return ;
			command_loop(data, data->last_cmd_executed->next);
		}
	}
}

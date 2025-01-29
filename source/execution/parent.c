/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:16:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/28 23:52:29 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(t_shell *data, t_cmd *command)
{

	data->commands_ran += 1;
	data->last_cmd_executed = command;
	if (command->delimiter != AND_DOUBLE && command->next)
		close(data->pipe_id[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (command->next)
		data->prev_fd = data->pipe_id[0];
	if (command->delimiter == PIPE_DOUBLE)
		return (1);
	if (command->delimiter == AND_DOUBLE)
		return 1;
	return (0);
}

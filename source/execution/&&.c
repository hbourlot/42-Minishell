/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   &&.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:05:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/20 11:18:55 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_and(t_cmd *command, pid_t *pid, int *pipe_id, int *prev_fd)
{
	if (command->next && command->next->next && do_pipe(pipe_id))
	{
		// ? ERROR case from do_pipe();
	}
	if (do_fork(pid))
		return (-1);
	else if (*pid == 0)
	{
		do_dup2(&command->fd_in, &command->fd_out, pipe_id, prev_fd);
	}
}
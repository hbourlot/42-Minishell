/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:00:01 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/23 16:02:14 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_fd(int fd1, int fd2)
{
	if (fd1 != -1)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
}

void	do_dup2(int *io, int *pipe_id, int *prev_fd)
{
	if (*prev_fd != -1)
		duplicate_fd(*prev_fd, STDIN_FILENO);
	if (io[0] != -1)
		duplicate_fd(io[0], STDIN_FILENO);
	if (io[1] != -1)
		duplicate_fd(io[1], STDOUT_FILENO);
	else
		duplicate_fd(pipe_id[1], STDOUT_FILENO);
	close_fd_safe(&pipe_id[1]);
	close_fd_safe(&pipe_id[0]);
}

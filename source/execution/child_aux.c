/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:00:01 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 13:14:35 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO: dup2 fails and return -1
static void	duplicate_fd(int fd1, int fd2)
{
	if (fd1 != -1)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
}

int	do_dup2(int *fd_in, int *fd_out,  int *pipe_id, int *prev_fd)
{
	if (prev_fd && *prev_fd != -1)
		duplicate_fd(*prev_fd, STDIN_FILENO);
	if (fd_in && *fd_in != -1)
		duplicate_fd(*fd_in, STDIN_FILENO);
	if (fd_out && *fd_out != -1)
		duplicate_fd(*fd_out, STDOUT_FILENO);
	else
		duplicate_fd(pipe_id[1], STDOUT_FILENO);
	if (pipe_id && pipe_id[1] != -1)
		close(pipe_id[1]);
	if (pipe_id && pipe_id[0] != -1)
		close(pipe_id[0]);
	return (0);
}


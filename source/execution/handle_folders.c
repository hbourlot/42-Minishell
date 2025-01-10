/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_folders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:00:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/02 23:31:16 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_folders_safety(int *in_fd, int *out_fd)
{
	if (*in_fd != -1)
		close(*in_fd);
	if (*out_fd != -1)
		close(*out_fd);
	*in_fd = -1;
	*out_fd = -1;
}

int	open_folders_safety(int *in_fd, int *out_fd, t_file *redir_files)
{
	while (redir_files)
	{
		if (redir_files->redirect == REDIRECT_LEFT_SINGLE)
		{
			*in_fd = open(redir_files->read, O_RDONLY);
			if (*in_fd < 0)
				return (set_error_execution(1, NO_FILE_DIR_MSG,
						redir_files->read, true), -1);
		}
		else if (redir_files->redirect == REDIRECT_RIGHT_SINGLE)
		{
			*out_fd = open(redir_files->write, O_CREAT | O_RDWR | O_TRUNC,
					0644);
			if (*out_fd < 0)
				return (close(*in_fd), -1);
		}
		else if (redir_files->redirect == REDIRECT_RIGHT_DOUBLE)
			*out_fd = open(redir_files->write, O_CREAT | O_RDWR | O_APPEND,
					0644);
		if (redir_files->next)
			close_folders_safety(in_fd, out_fd);
		redir_files = redir_files->next;
	}
	return (0);
}

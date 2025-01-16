/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_folders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:00:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/14 15:28:46 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_folders_safety(int *fd_in, int *fd_out)
{
	if (*fd_in != -1)
		close(*fd_in);
	if (*fd_out != -1)
		close(*fd_out);
	*fd_in = -1;
	*fd_out = -1;
}

int	open_folders_safety(int *fd_in, int *fd_out, t_file *redir_files)
{
	while (redir_files)
	{
		if (redir_files->redirect == REDIRECT_LEFT_SINGLE)
		{
			*fd_in = open(redir_files->read, O_RDONLY);
			if (*fd_in < 0)
				return (set_error_execution(1, NO_FILE_DIR_MSG,
						redir_files->read, true), -1);
		}
		else if (redir_files->redirect == REDIRECT_RIGHT_SINGLE)
		{
			*fd_out = open(redir_files->write, O_CREAT | O_RDWR | O_TRUNC,
					0644);
			if (*fd_out < 0)
				return (close(*fd_in), -1);
		}
		else if (redir_files->redirect == REDIRECT_RIGHT_DOUBLE)
			*fd_out = open(redir_files->write, O_CREAT | O_RDWR | O_APPEND,
					0644);
		if (redir_files->next)
			close_folders_safety(fd_in, fd_out);
		redir_files = redir_files->next;
	}
	return (0);
}

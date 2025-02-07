/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_folders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:00:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/06 16:33:06 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_folders_safety(t_file *redir_files, int *io)
{
	if (redir_files->next->read)
		if (io[0] != -1)
		{
			close(io[0]);
			io[0] = -1;
		}
	if (redir_files->next->write)
		if (io[1] != -1)
		{
			close(io[1]);
			io[1] = -1;
		}
}

int	open_folders_safety(int *io, t_file *redir_files)
{
	int	code;
	
	while (redir_files)
	{
		if (redir_files->redirect == REDIRECT_LEFT_SINGLE)
		{
			io[0] = open(redir_files->read, O_RDONLY);
			if (io[0] < 0)
			{
				return (set_error_ex(1, NO_FILE_DIR_MSG,
						redir_files->read, true), -1);
			}
		}
		else if (redir_files->redirect == REDIRECT_RIGHT_SINGLE)
		{
			io[1] = open(redir_files->write, O_CREAT | O_RDWR | O_TRUNC,
					0644);
			if (io[1] < 0)
			{
				code = validate_command_path_access(redir_files->write);
				return (set_error_ex(1, NULL, NULL, true), -1);
			}
		}
		else if (redir_files->redirect == REDIRECT_RIGHT_DOUBLE)
			io[1] = open(redir_files->write, O_CREAT | O_RDWR | O_APPEND,
					0644);
		if (redir_files->next)
			close_folders_safety(redir_files, io);
		redir_files = redir_files->next;
	}
	return (0);
}

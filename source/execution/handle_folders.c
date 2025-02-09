/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_folders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:00:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/09 21:19:20 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_folders_safety(t_file *rf, int *io)
{
	if (rf->next->read)
		if (io[0] != -1)
		{
			close(io[0]);
			io[0] = -1;
		}
	if (rf->next->write)
		if (io[1] != -1)
		{
			close(io[1]);
			io[1] = -1;
		}
}

void	open_folders_safety(int *io, t_file *rf)
{
	int	code;
	
	while (rf)
	{
		if (rf->redirect == REDIRECT_LEFT_SINGLE)
		{
			io[0] = open(rf->read, O_RDONLY);
			if (io[0] < 0)
			{
				handle_error(E_FILE_DIR, rf->read, NULL);
				// return (set_error_ex(1, NO_FILE_DIR_MSG,
				// 		rf->read, true), -1);
			}
		}
		else if (rf->redirect == REDIRECT_RIGHT_SINGLE)
		{
			io[1] = open(rf->write, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (io[1] < 0)
			{
				code = validate_command_path_access(rf->write);
				handle_error(code, NULL, NULL);
			}
		}
		else if (rf->redirect == REDIRECT_RIGHT_DOUBLE)
		{
			io[1] = open(rf->write, O_CREAT | O_RDWR | O_APPEND,
					0644);
			if (io[1] < 0)
			{
				code = validate_command_path_access(rf->write);
				handle_error(code, NULL, NULL);
			}
		}
		if (rf->next)
			close_folders_safety(rf, io);
		rf = rf->next;
	}
}

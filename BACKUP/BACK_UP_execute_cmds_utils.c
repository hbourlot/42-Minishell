/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:45:07 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 12:00:29 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	duplicate_fd(int fd1, int fd2)
{
	if (fd1 != -1)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
}

int	open_folder(char *file, t_cmd *command, bool here_doc)
{
	if (command->in_fd == READ)
	{
		command->in_fd = open(file, O_RDONLY);
		if (command->in_fd < 0)
			return (-1);
	}
	if (command->out_fd == WRITE && !here_doc)
	{
		if (command->delimiter == REDIRECT_LEFT_DOUBLE || command->delimiter == REDIRECT_RIGHT_DOUBLE)
			command->out_fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			command->out_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (command->out_fd < 0)
			return (close(command->in_fd), -1);
	}
	if (command->out_fd == WRITE && here_doc)
	{
		if (command->delimiter == REDIRECT_LEFT_DOUBLE || command->delimiter == REDIRECT_RIGHT_DOUBLE)
			command->out_fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			command->out_fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (command->out_fd < 0)
			return (close(command->in_fd), -1);
	}
	return (0);
}

int	do_dup2(t_cmd *command, int *pipe_id, int *prev_fd)
{
	int	status;

	status = 0;
	if (*prev_fd != -1)
	{
		duplicate_fd(*prev_fd, STDIN_FILENO);
	}
	if (command->in_fd == READ)
	{
		// status = open_folder(command->file_list[0], command, command->settings.here_doc);
		status = open_folder(command->file, command, command->settings.here_doc);
		duplicate_fd(command->in_fd, STDIN_FILENO);
	}
	if (command->out_fd == WRITE)
	{
		// status = open_folder(command->file_list[0], command, command->settings.here_doc);
		status = open_folder(command->file, command, command->settings.here_doc);
		duplicate_fd(command->out_fd, STDOUT_FILENO);
	}
	else
		dup2(pipe_id[1], STDOUT_FILENO);
	if (pipe_id[1] != -1)
		close(pipe_id[1]);
	if (pipe_id[0] != -1)
		close(pipe_id[0]);
	return (status);
}


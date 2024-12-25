/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:00:01 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 12:52:35 by hbourlot         ###   ########.fr       */
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

static int open_folders(t_cmd *command)
{
	t_file 	*file;
	
	file = command->file_list;
	while (file)
	{
		if (file->redirect == REDIRECT_LEFT_SINGLE)
		{
			command->in_fd = open(file->read, O_RDONLY);
			if (command->in_fd < 0)
				return (ERROR);
		}
		// else if (file->redirect == REDIRECT_LEFT_DOUBLE) // TODO: HERE_DOC CASE
		// 	command->in_fd = open(file->read, O_CREAT | O_RDWR, O_APPEND, 0644);
		else if (file->redirect == REDIRECT_RIGHT_SINGLE)
		{
			printf("SINGE_RIGHT\n");
			command->out_fd = open(file->write, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (command->out_fd < 0)
			{
				printf("file_name(ERROR): %s\n", file->write);
				return (close(command->in_fd), ERROR);
			}
		}
		else if (file->redirect == REDIRECT_RIGHT_DOUBLE)
			command->out_fd = open(file->write, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (file->next)
		{
			close(command->in_fd);
			close(command->out_fd);
			command->in_fd = -1;
			command->out_fd = -1;
		}
		file = file->next;
	}
	return (0);
}

int	do_dup2(t_cmd *command, int *pipe_id, int *prev_fd)
{
	t_file	*tmp_file_list;
	
	if (*prev_fd != -1)
		duplicate_fd(*prev_fd, STDIN_FILENO);
	if (open_folders(command) < 0)
		return (ERROR);
	if (command->in_fd != -1)
		duplicate_fd(command->in_fd, STDIN_FILENO);
	if (command->out_fd != -1)
		duplicate_fd(command->out_fd, STDOUT_FILENO);
	else
		duplicate_fd(pipe_id[1], STDOUT_FILENO);
	if (pipe_id[1] != -1)
		close(pipe_id[1]);
	if (pipe_id[0] != -1)
		close(pipe_id[0]);
	return (0);
}

// typedef enum e_delimiter
// {
// 	PIPE_SINGLE,          // single pipe `|`
// 	PIPE_DOUBLE,          // double pipe `||`
// 	AND_SINGLE,           // single AND `&`
// 	AND_DOUBLE,           // double AND `&&`
// 	REDIRECT_RIGHT_SINGLE, // single right redirection `>`
// 	REDIRECT_RIGHT_DOUBLE, // double right redirection `>>`
// 	REDIRECT_LEFT_SINGLE,  // single left redirection `<`
// 	REDIRECT_LEFT_DOUBLE   // double left redirection `<<`
// }	t_delimiter;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 12:00:01 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/10 14:59:53 by joralves         ###   ########.fr       */
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

int	do_dup2(t_cmd *command, int *pipe_id, int *prev_fd)
{
	if (*prev_fd != -1)
		duplicate_fd(*prev_fd, STDIN_FILENO);
	if (command->fd_in != -1)
		duplicate_fd(command->fd_in, STDIN_FILENO);
	if (command->fd_out != -1)
		duplicate_fd(command->fd_out, STDOUT_FILENO);
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
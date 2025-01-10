/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_eof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/06 20:04:26 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	cleanup_and_exit(char *text, int error_code)
// {
// 	if (text)
// 		free(text);
// 	write(1, "\n", 1);
// 	return (error_code);
// }

// static int	here_doc(char **eof, int fd)
// {
// 	int		i;
// 	char	*text;
// 	char	*limiter;

// 	i = 0;
// 	while (eof && eof[i])
// 	{
// 		limiter = eof[i];
// 		while (true)
// 		{
// 			ft_putstr_fd("> ", STDOUT_FILENO);
// 			text = get_next_line(STDIN_FILENO);
// 			if (!text)
// 				return (-1);
// 			if (ft_strcmp(limiter, text) == CMP_OK)
// 				break ;
// 			if (ft_strlen(text) == 0) // TODO: CTRL + D: bash: warning: here-document at line 10 delimited by end-of-file (wanted `EOF')
// 				return (free(text), -1);
// 			if (!ft_strchr(text, '\n') && !ft_strncmp(text, limiter, ft_strlen(text)
// 					- 1))
// 				return (free(text), -1);
// 			ft_putstr_fd(text, fd);
// 			free(text);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	run_eof(t_cmd *command, int *pipe_id, int *prev_fd)
// {
// 	if (pipe_id[0] != -1)
// 	{
// 		printf("FECHEI PIPE_ID[0]\n");
// 		close(pipe_id[0]);
// 	}
// 	here_doc(command->settings.eof, pipe_id[1]);
// 	close(pipe_id[1]);
// 	// Dont know what to do
// 	return (0);
// }


//* typedef struct s_pipe_info
//* {
//* 	int				pipe_id[2];
//* 	int				prev_fd;
//* }					t_pipe_info;

//* typedef struct s_process_info
//* {
//* 	int				wait;
//* 	int				w_status;
//* 	pid_t			pid;
//* }					t_process_info;





static int	cleanup_and_exit(char *text, int error_code)
{
	if (text)
		free(text);
	return (error_code);
}

int	here_doc(int *pipe_id, char *limiter)
{
	char	*text;

	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		text = get_next_line(STDIN_FILENO);
		if (!text)
			return (cleanup_and_exit(NULL, -1));
		if (!ft_strcmp(limiter, text))
			break ;
		if (ft_strlen(text) == 0)
			return (cleanup_and_exit(text, -1));
		if (!ft_strchr(text, '\n') && !ft_strncmp(text, limiter, ft_strlen(text)
				- 1))
			return (cleanup_and_exit(text, -1));
		ft_putstr_fd(text, pipe_id[1]);
		free(text);
	}
	return (cleanup_and_exit(text, 0));
}

static void	handle_child_process(t_cmd *command, int *pipe_id, int *prev_fd)
{
	int		i;

	i = 0;
	// if (*prev_fd != -1)
	close(pipe_id[0]);
	while (command->settings.eof[i])
	{
		if (here_doc(pipe_id, command->settings.eof[i]) == -1)
		{
			close(pipe_id[1]);
			perror("read_eof error.");
			cleanup_shell(get_shell());
			exit(EXIT_FAILURE);
			// ft_close(1, data, "Error reading EOF");
		}
		i++;
	}
	write(1, "\n", 1);
	close(pipe_id[1]);
	cleanup_shell(get_shell());
	exit(EXIT_SUCCESS);
}

static void	handle_parent_process(int *pipe_id, int *prev_fd, pid_t *pid)
{
	pid_t	result;
	int		wait_status;
	
	close(pipe_id[1]);
	result = waitpid(*pid, &wait_status, 0);
	if (wait_status < 0)
	{
		perror("Error no status");
		//! Exit
		// ft_close(1, data, "Wait error");
	}
	*prev_fd = pipe_id[0];
}

int	run_eof(t_cmd *command, int *pipe_id, int *prev_fd, pid_t *pid)
{
	if (pipe(pipe_id) == -1)
		perror("ERROR PIPE HERE_DOC");
		// ft_close(1, data, "Pipe Error");
	*pid = fork();
	if (*pid == -1)
		perror("Error fork here_doc");
		// ft_close(1, data, "Fork Error");
	if (*pid == 0)
		handle_child_process(command, pipe_id, prev_fd);
	else
		handle_parent_process(pipe_id, prev_fd, pid);
	return (0);
}
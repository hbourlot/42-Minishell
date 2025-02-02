/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 18:45:22 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

static void	handle_child_process(t_shell *data)
{
	int	i;

	i = 0;
	handle_signals(data, 1);
	while (data->eof && data->eof[i])
	{
		if (here_doc(data->pipe_id, data->eof[i]) == -1)
		{
			close(data->pipe_id[1]);
			set_error_ex(1, "Failed", "here_doc", true);
			handle_error();
		}
		i++;
	}
	if (!data->command) // TODO: Still need to make sure about it
		write(1, "\n", 1);
	close(data->pipe_id[0]);
	close(data->pipe_id[1]);
	cleanup_shell(data);
	exit(EXIT_SUCCESS);
}

static int	handle_parent_process(t_shell *data, pid_t *pid)
{
	int		wait_status;
	
	if (data->command)
		data->prev_fd = data->pipe_id[0];
	else
		close(data->pipe_id[0]);
	*pid = waitpid(-1, &wait_status, 0);
	if (WIFEXITED(wait_status))
	{
		data->exit_status = WEXITSTATUS(wait_status);
		if (data->exit_status == 130)
		{
			setup_signals();
			return -1;
		}
	}
	close(data->pipe_id[1]);
	return 0;
}

int	run_eof(t_shell *data, pid_t *pid)
{
	if (pipe(data->pipe_id) == -1)
		perror("Pipe"); // TODO: !!!!!
	*pid = fork(); // TODO: !!!!!
	if (*pid == -1)
		perror("Fork");
	if (*pid == 0)
		handle_child_process(data);
	if (handle_parent_process(data, pid))
		return (-1);
	return (0);
}

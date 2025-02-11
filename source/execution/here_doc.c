/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 17:30:22 by hbourlot         ###   ########.fr       */
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

static void	handle_child_process(t_shell *data, int i)
{
	restore_signals();
	if (here_doc(data->pipe_id, data->eof[i]) == -1)
		here_doc_fail(data, data->eof[i]);
	cleanup_shell(data);
	exit(EXIT_SUCCESS);
}

static void	handle_parent_process(t_shell *data, int i, int *ws)
{
	if (!data->eof[i + 1] && data->command)
		data->prev_fd = data->pipe_id[0];
	else
		close(data->pipe_id[0]);
	wait(ws);
	close(data->pipe_id[1]);
}

int	run_eof(t_shell *data, pid_t *pid)
{
	int	i;
	int	wait_status;

	i = 0;
	while (data->eof[i])
	{
		signal(SIGINT, SIG_IGN);
		if (pipe(data->pipe_id) == -1 || do_fork(&data->pid))
			return (handle_error(E_PF, NULL, NULL), -1);
		else if (*pid == 0)
			handle_child_process(data, i);
		else
			handle_parent_process(data, i, &wait_status);
		if (WIFEXITED(wait_status))
		{
			data->exit_status = WEXITSTATUS(wait_status);
			if (data->exit_status)
				return (-1);
		}
		i++;
	}
	return (0);
}

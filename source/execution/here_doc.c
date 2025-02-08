/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/07 15:14:23 by hbourlot         ###   ########.fr       */
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


static void	here_doc_fail(t_shell *data, char *eof)
{
	int	size;

	size = ft_strlen(eof);
	get_error_context()->exit = true;
	truncate_range(eof, size - 1, 1);
	ft_printf_error("\nbash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", data->nbr_of_lines, eof);
	handle_error();

}

static void	handle_child_process(t_shell *data, int i)
{
	restore_signals();
	if (here_doc(data->pipe_id, data->eof[i]) == -1)
		here_doc_fail(data, data->eof[i]);
	close(data->pipe_id[0]);
	close(data->pipe_id[1]);
	cleanup_shell(data);
	exit(EXIT_SUCCESS);
}

static void	handle_parent_process(t_shell *data, int i, int *ws)
{
	int	e;
	
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
			return (set_error_ex(1, "Pipe/Fork", NULL, false), -1);
		else if (*pid == 0)
			handle_child_process(data, i);
		else
			handle_parent_process(data, i, &wait_status);
		if (WIFEXITED(wait_status))
			return 1;
		i++;
	}

	return (0);
}


// int	run_eof(t_shell *data, pid_t *pid)
// {
// 	if (pipe(data->pipe_id) == -1)
// 		perror("Pipe");
// 	signal(SIGINT, SIG_IGN);
// 	*pid = fork();
// 	if (*pid == -1)
// 		perror("Fork");
// 	if (*pid == 0)
// 	{
// 		restore_signals();
// 		handle_child_process(data);
// 	}
// 	if (handle_parent_process(data))
// 		return (-1);
// 	return (0);
// }
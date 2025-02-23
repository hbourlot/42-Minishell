/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/23 16:07:38 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_in_pipe(t_file *current, char **text)
{
	char	*expanded;

	if (!current->in_quotes)
	{
		expanded = expand_command_input(*text, NULL);
		free(*text);
		*text = expanded;
	}
}

int	here_doc(int *pipe_id, t_file *current)
{
	char	*text;

	while (true)
	{
		text = readline("> ");
		if (!text)
			return (-1);
		if (ft_strlen(text) == 0)
		{
			free(text);
			continue ;
		}
		if (!ft_strcmp(current->read, text))
			return (free(text), 0);
		expand_in_pipe(current, &text);
		ft_printf_fd(pipe_id[1], "%s\n", text);
		free(text);
	}
	return (0);
}

static void	handle_cprocess(t_shell *data, t_file *current)
{
	restore_signals(EOF);
	if (here_doc(data->pipe_id, current) == -1)
		here_doc_fail(data, current);
	cleanup_shell(data);
	close_fd_safe(&data->pipe_id[0]);
	close_fd_safe(&data->pipe_id[1]);
	exit(EXIT_SUCCESS);
}

static int	handle_pprocess(t_shell *data, t_cmd *command)
{
	int	ws;

	waitpid(data->pid, &ws, 0);
	if (command->settings.iste)
		data->prev_fd = data->pipe_id[0];
	else
		close_fd_safe(&data->pipe_id[0]);
	close_fd_safe(&data->pipe_id[1]);
	if (WIFSIGNALED(ws) && WIFEXITED(ws))
	{
		close_fd_safe(&data->pipe_id[0]);
		close_fd_safe(&data->pipe_id[1]);
		data->exit_status = WTERMSIG(ws) + 128;
		return (-1);
	}
	if (WIFEXITED(ws))
	{
		close_fd_safe(&data->pipe_id[1]);
		data->exit_status = WEXITSTATUS(ws);
		if (data->exit_status)
			return (-1);
	}
	return (0);
}

int	run_eof(t_shell *data, t_cmd *command)
{
	int		i;
	t_file	*current;

	i = 0;
	current = command->eof_rf;
	while (current)
	{
		close_fd_safe(&data->prev_fd);
		if (current->redirect == REDIRECT_LEFT_DOUBLE)
		{
			signal(SIGINT, SIG_IGN);
			if (pipe(data->pipe_id) < 0 || do_fork(&data->pid))
				return (handle_error(E_PF, NULL, NULL), -1);
			if (data->pid == 0)
				handle_cprocess(data, current);
			else
			{
				if (handle_pprocess(data, command))
					return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

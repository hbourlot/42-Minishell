/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/21 16:28:30 by joralves         ###   ########.fr       */
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

static void	handle_grand_child_process(t_shell *data, t_file *current)
{
	restore_signals(EOF);
	if (here_doc(data->pipe_id, current) == -1)
		here_doc_fail(data, current);
	cleanup_shell(data);
	close(data->pipe_id[0]);
	close(data->pipe_id[1]);
	exit(EXIT_SUCCESS);
}

static int	handle_parent_process(t_shell *data, t_cmd *command,
		t_file *current)
{
	int	ws;

	if (!current->next && command->settings.iste)
		data->prev_fd = data->pipe_id[0];
	else
		close_fd_safe(data->pipe_id[0]);
	close_fd_safe(data->pipe_id[1]);
	wait(&ws);
	if (WIFSIGNALED(ws))
	{
		data->exit_status = WTERMSIG(ws) + 128;
		return (-1);
	}
	if (WIFEXITED(ws))
	{
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
	pid_t	pid;

	i = 0;
	current = command->eof_rf;
	while (current)
	{
		if (current->redirect == REDIRECT_LEFT_DOUBLE)
		{
			signal(SIGINT, SIG_IGN);
			if (pipe(data->pipe_id) < 0 || do_fork(&pid))
				return (handle_error(E_PF, NULL, NULL), -1);
			if (pid == 0)
				handle_grand_child_process(data, current);
			else
			{
				if (handle_parent_process(data, command, current))
					return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

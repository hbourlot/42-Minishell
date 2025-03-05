/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/05 17:57:15 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cprocess(t_shell *data, t_file *current)
{
	t_cmd	*tmp;

	restore_signals(EOF);
	tmp = data->command;
	while (tmp)
	{
		close_fd_safe(&tmp->fd_eof);
		tmp = tmp->next;
	}
	if (here_doc(data->pipe_id, current) == -1)
		here_doc_fail(data, current);
	cleanup_shell(data);
	close_fd_safe(&data->pipe_id[0]);
	close_fd_safe(&data->pipe_id[1]);
	exit(EXIT_SUCCESS);
}

static void	handle_pprocess(t_shell *data, t_cmd *command)
{
	int	ws;

	waitpid(data->pid, &ws, 0);
	if (command->settings.iste)
	{
		close_fd_safe(&command->fd_eof);
		command->fd_eof = data->pipe_id[0];
	}
	else
		close_fd_safe(&data->pipe_id[0]);
	close_fd_safe(&data->pipe_id[1]);
	if (WIFSIGNALED(ws) && WIFEXITED(ws))
	{
		close_fd_safe(&data->pipe_id[0]);
		close_fd_safe(&data->pipe_id[1]);
		data->exit_status = WTERMSIG(ws) + 128;
		return ;
	}
	if (WIFEXITED(ws))
	{
		close_fd_safe(&data->pipe_id[1]);
		data->exit_status = WEXITSTATUS(ws);
		return ;
	}
}

int	process_eof_redirects(t_shell *data, t_cmd *command)
{
	t_file	*current;

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
				handle_pprocess(data, command);
				if (data->exit_status)
					return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	run_eof(t_shell *data, t_cmd *command)
{
	while (command)
	{
		if (process_eof_redirects(data, command) < 0)
			return (-1);
		command = command->next;
	}
	return (0);
}

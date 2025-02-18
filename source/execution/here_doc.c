/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/18 20:04:32 by hbourlot         ###   ########.fr       */
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
			break ;
		if (!ft_strchr(text, '\n') && !ft_strncmp(text, current->read,
				ft_strlen(text)))
			return (free(text), -1);
		expand_in_pipe(current, &text);
		ft_putstr_fd(text, pipe_id[1]);
		ft_putstr_fd("\n", pipe_id[1]);
		free(text);
	}
	if (text)
		free(text);
	return (0);
}

static void	handle_child_process(t_shell *data, t_file *current)
{
	restore_signals(EOF);
	if (here_doc(data->pipe_id, current) == -1)
		here_doc_fail(data, current);
	cleanup_shell(data);
	close(data->pipe_id[0]);
	close(data->pipe_id[1]);
	exit(EXIT_SUCCESS);
}

static void	handle_parent_process(t_shell *data, t_cmd *command, t_file *current, int *ws)
{
	if (!current->next && command->settings.is_safe_to_execve)
		data->prev_fd = data->pipe_id[0];
	else
		close(data->pipe_id[0]);
	wait(ws);
	close(data->pipe_id[1]);
}

int	run_eof(t_shell *data, t_cmd *command)
{
	int		i;
	int		wait_status;
	t_file	*current;

	i = 0;
	current = command->eof;
	while (current)
	{
		if (current->redirect == REDIRECT_LEFT_DOUBLE)
		{
			if (data->prev_fd != -1)
				close(data->prev_fd);
			signal(SIGINT, SIG_IGN);
			if (pipe(data->pipe_id) == -1 || do_fork(&data->pid))
				return (handle_error(E_PF, NULL, NULL), -1);
			else if (data->pid == 0)
				handle_child_process(data, current);
			else
				handle_parent_process(data, command, current, &wait_status);
			if (WIFEXITED(wait_status))
			{
				data->exit_status = WEXITSTATUS(wait_status);
				if (data->exit_status)
					return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   here_doc.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/30 14:06:50 by hbourlot          #+#    #+#             */
// /*   Updated: 2025/02/18 16:33:25 by hbourlot         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// static void	expand_in_pipe(t_file *current, char **text)
// {
// 	char	*expanded;

// 	if (!current->in_quotes)
// 	{
// 		expanded = expand_command_input(*text, NULL);
// 		free(*text);
// 		*text = expanded;
// 	}
// }

// int	here_doc(int *pipe_id, t_file *current)
// {
// 	char	*text;

// 	while (true)
// 	{
// 		text = readline("> ");
// 		if (!text)
// 			return (-1);
// 		if (ft_strlen(text) == 0)
// 		{
// 			free(text);
// 			continue ;
// 		}
// 		if (!ft_strcmp(current->eof, text))
// 			break ;
// 		if (!ft_strchr(text, '\n') && !ft_strncmp(text, current->eof,
// 				ft_strlen(text)))
// 			return (free(text), -1);
// 		expand_in_pipe(current, &text);
// 		ft_putstr_fd(text, pipe_id[1]);
// 		ft_putstr_fd("\n", pipe_id[1]);
// 		free(text);
// 	}
// 	if (text)
// 		free(text);
// 	return (0);
// }

// static void	handle_child_process(t_shell *data, t_file *current)
// {
// 	restore_signals(EOF);
// 	if (here_doc(data->pipe_id, current) == -1)
// 		here_doc_fail(data, current);
// 	cleanup_shell(data);
// 	exit(EXIT_SUCCESS);
// }

// static void	handle_parent_process(t_shell *data, t_file *current, int *ws)
// {
// 	if (!current->next && data->command)
// 		data->prev_fd = data->pipe_id[0];
// 	else
// 		close(data->pipe_id[0]);
// 	wait(ws);
// 	close(data->pipe_id[1]);
// }

// int	run_eof(t_shell *data, pid_t *pid)
// {
// 	int		i;
// 	int		wait_status;
// 	t_file	*current;

// 	i = 0;
// 	current = data->rf;
// 	while (current)
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		if (pipe(data->pipe_id) == -1 || do_fork(&data->pid))
// 			return (handle_error(E_PF, NULL, NULL), -1);
// 		else if (*pid == 0)
// 			handle_child_process(data, current);
// 		else
// 			handle_parent_process(data, current, &wait_status);
// 		if (WIFEXITED(wait_status))
// 		{
// 			data->exit_status = WEXITSTATUS(wait_status);
// 			if (data->exit_status)
// 				return (-1);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

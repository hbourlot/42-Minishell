/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:00:26 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/21 18:51:46 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_only_tokens(t_cmd *command)
{
	int	code_parsing;

	code_parsing = 0;
	code_parsing = validate_file_read_execution(command->io_rf);
	if (code_parsing)
		handle_error(E_VFRE, NULL, NULL);
	return ;
}

static bool	is_safe_to_execve(t_cmd *command)
{
	if (command->settings.only_tokens)
		return (false);
	if (command->settings.expansion && ft_strlen(command->path) == 0)
		return (false);
	if (command->settings.is_builtin)
		return (false);
	if (command->settings.iste == false)
		return (false);
	return (true);
}

void	exec_builtin(t_shell *data, t_cmd *command)
{
	if (command->settings.istb && process_builtin(data, command, 1) < 0)
		handle_error(E_MALLOC, NULL, __func__);
}

static void	exec_heredoc(t_shell *data, t_cmd *command)
{
	if (command->eof_rf)
	{
		close_fd_safe(data->pipe_id[0]);
		close_fd_safe(data->pipe_id[1]);
		close_fd_safe(data->prev_fd);
		run_eof(data, command);
		if (data->exit_status == 130 || data->exit_status == 131)
		{
			cleanup_shell(data);
			exit(data->exit_status);
		}
		if (!command->io_rf && command->next)
		{
			if (pipe(data->pipe_id) < 0)
				handle_error(E_PF, NULL, __func__);
			close_fd_safe(data->pipe_id[0]);
			dup2(data->pipe_id[1], STDOUT_FILENO);
			close_fd_safe(data->pipe_id[1]);
		}
	}
}

void	child_process(t_shell *data, t_cmd *command)
{
	int	code;

	restore_signals(0);
	exec_heredoc(data, command);
	if (command->settings.only_tokens)
		execute_only_tokens(command);
	open_folders_safety(command->io, command->io_rf);
	do_dup2(command->io, data->pipe_id, &data->prev_fd);
	if (is_safe_to_execve(command))
	{
		execve(command->path, command->args, data->envp);
		code = validate_command_path_access(command->path);
		handle_error(code, NULL, NULL);
	}
	exec_builtin(data, command);
	cleanup_shell(data);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:00:26 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/07 23:12:29 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_only_tokens(t_shell *data, t_cmd *command)
{
	int	code_parsing;

	code_parsing = 0;
	code_parsing = validate_file_read_execution(command->redir_files);
	if (code_parsing)
	{
		set_error_ex(code_parsing, NULL, NULL, true);
		cleanup_shell(data);
		handle_error();
	}
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
	if (command->settings.is_safe_to_execve == false)
		return (false);
	return (true);
}

void	exec_builtin(t_shell *data, t_cmd *command)
{
	if (command->settings.is_safe_to_builtin && process_builtin(data,
			command) < 0)
	{
		set_error_ex(1, "Malloc", NULL, true);
		handle_error();
	}
}

void	child_process(t_shell *data, t_cmd *command)
{
	int	code;

	if (command->settings.only_tokens)
		execute_only_tokens(data, command);
	if (open_folders_safety(command->io, command->redir_files))
		exit(handle_error());
	do_dup2(command->io, data->pipe_id, &data->prev_fd);
	if (is_safe_to_execve(command))
	{
		execve(command->path, command->args, command->envp);
		code = validate_command_path_access(command->path);
		set_error_ex(code, NULL, NULL, true);
		handle_error();
	}
	exec_builtin(data, command);
	cleanup_shell(data);
	exit(0);
}

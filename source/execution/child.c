/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:00:26 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 09:17:01 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_only_tokens(t_shell *data, t_cmd *command)
{
	int	code_parsing;

	code_parsing = 0;
	code_parsing = (validate_file_read_execution(command->redir_files) 
					|| validate_command_path_access(command->path));
	// ! Pretty sure dont need to validate command_path_access since its only files to handle;
	if (code_parsing)
	{
		set_error_execution(code_parsing, NULL, NULL, true);
		cleanup_shell(data);
		handle_error();
	}
	return;
}

static bool is_safe_to_execute(t_cmd *command)
{
	if (command->settings.only_tokens)
		return (false);
	if (command->settings.expansion && ft_strlen(command->path) == 0)
		return (false);
	if (command->settings.is_builtin)
		return (false);

	return (true);
}

void	child_process(t_shell *data, t_cmd *command)
{
	int	code;

	handle_signals(data, 1);
	if (command->settings.only_tokens)
		execute_only_tokens(data, command);
	if (open_folders_safety(&command->fd_in, &command->fd_out, command->redir_files))
		exit(handle_error());
	if (do_dup2(&command->fd_in, &command->fd_out, data->pipe_id, &data->prev_fd))
	{
		cleanup_shell(data);
		exit(EXIT_FAILURE);
	}
	if (is_safe_to_execute(command))
	{
		execve(command->path, command->args, command->envp);
		code = validate_command_path_access(command->path);
		set_error_execution(code, NULL, NULL, true);
		handle_error();
	}
	if (command->settings.is_builtin)
		process_builtin(data, command);
	cleanup_shell(data);
	exit(0);
}

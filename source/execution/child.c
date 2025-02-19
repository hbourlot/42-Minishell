/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:00:26 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/19 14:26:29 by hbourlot         ###   ########.fr       */
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
	if (command->settings.istb && process_builtin(data,
			command, 1) < 0)
		handle_error(E_MALLOC, NULL, __func__);
}

void	child_process(t_shell *data, t_cmd *command)
{
	int	code;
	if (command->path)
		ft_printf_fd(2, "command->path: %s\n", command->path);
	restore_signals(0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:00:26 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/05 17:57:43 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_safe_to_execve(t_cmd *command)
{
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

void	close_duplicate_fd(t_shell *data, t_cmd *command)
{
	t_cmd	*tmp;

	tmp = data->command;
	while (tmp)
	{
		if ((tmp == command) && tmp->fd_eof != -1)
		{
			tmp = tmp->next;
			continue ;
		}
		close_fd_safe(&tmp->fd_eof);
		tmp = tmp->next;
	}
}

void	child_process(t_shell *data, t_cmd *command)
{
	int		code;

	restore_signals(0);
	close_duplicate_fd(data, command);
	if (command->fd_eof != -1)
	{
		close_fd_safe(&data->prev_fd);
		data->prev_fd = command->fd_eof;
	}
	if (validate_file_read_execution(command->io_rf))
		handle_error(E_VFRE, NULL, NULL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:16:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/18 17:49:56 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_double_and(t_shell *data, t_cmd **command_ref)
{
	t_cmd	*current;

	set_last_status(data);
	if (data->exit_status == 0)
		return (0);
	current = *command_ref;
	while (current && current->delimiter != PIPE_DOUBLE)
		current = current->next;
	if (current && current->delimiter == PIPE_DOUBLE)
	{
		*command_ref = current;
		return (0);
	}
	return (1);
}

int	print_command_on_terminal(t_shell *data)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	close(data->pipe_id[1]);
	bytes_read = read(data->pipe_id[0], buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
		return (-1);
	buffer[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(data->pipe_id[0], buffer, sizeof(buffer) - 1);
		if (bytes_read < 0)
			return (-1);
		buffer[bytes_read] = '\0';
	}
	close(data->pipe_id[0]);
	return (0);
}

int	parent_process(t_shell *data, t_cmd **command_ref)
{
	data->commands_ran += 1;
	data->last_cmd_executed = (*command_ref);
	if ((*command_ref)->delimiter != AND_DOUBLE && (*command_ref)->next)
	{
		if ((*command_ref)->settings.is_builtin)
			wait(NULL);
		close(data->pipe_id[1]);
	}
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if ((*command_ref)->next)
		data->prev_fd = data->pipe_id[0];
	if ((*command_ref)->delimiter == PIPE_DOUBLE)
	{
		set_last_status(data);
		if (data->exit_status == 0)
		{
			print_command_on_terminal(data);
			return (1);
		}
	}
	if ((*command_ref)->delimiter == AND_DOUBLE)
		return (handle_double_and(data, command_ref));
	return (0);
}

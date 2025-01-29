/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:29:15 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/28 21:29:29 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_double_pipe(t_shell *data)
{
	while (data->commands_ran < data->nbr_of_commands)
	{
		set_last_status(data);
		if (data->exit_status == 0)
		{
			if (print_command_on_terminal(data, &data->pid) < 0)
			{
				set_error_execution(1, "Read", NULL, 0);
				handle_error();
			}
			return 1;
		}
		command_loop(data, data->last_cmd_executed->next);
	}
	return 0;
}

int	print_command_on_terminal(t_shell *data, pid_t *pid)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	close(data->pipe_id[1]);
	bytes_read = read(data->pipe_id[0], buffer, sizeof(buffer) -1);
	if (bytes_read < 0)
		return (-1);
	buffer[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(data->pipe_id[0], buffer, sizeof(buffer) -1);
		if (bytes_read < 0)
			return (-1);
		buffer[bytes_read] = '\0';
	}
	close(data->pipe_id[0]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ||.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:29:15 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/20 15:29:39 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

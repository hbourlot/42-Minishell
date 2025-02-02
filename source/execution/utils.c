/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:56 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 18:39:47 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_status(t_shell *data)
{
	int		status;
	int		wait_status;
	pid_t	prev_pid;
	int		i;

	i = 0;
	prev_pid = 0;	
	wait_status = 0;
	while (i < data->commands_ran)
	{
		data->pid = waitpid(-1, &wait_status, 0);
		if (WIFEXITED(wait_status) && data->pid > prev_pid)
			status = WEXITSTATUS(wait_status);
		prev_pid = data->pid;
		i++;
	}

	data->exit_status = status;
}

int	do_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
		return (-1);
	return (0);
}








// bool	there_is_command_single_pipe(t_shell *data)
// {
// 	t_cmd *current;

// 	current = data->command;

// 	if (data->nbr_of_commands == 1)
// 		return false;
// 	while (current)
// 	{
// 		if (current->delimiter == PIPE_SINGLE)
// 			return true;
// 		current = current->next;
// 	}
// 	return false;
// }
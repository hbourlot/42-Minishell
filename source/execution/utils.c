/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:56 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/04 12:58:00 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_wait_stats(int wait_status, int *status)
{
	int	sig;

	if (WIFEXITED(wait_status))
		*status = WEXITSTATUS(wait_status);
	else if (WIFSIGNALED(wait_status))
	{
		sig = WTERMSIG(wait_status);
		*status = 128 + sig;
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(1, "\n", 1);
	}
}

void	set_last_status(t_shell *data)
{
	int		status;
	int		wait_status;
	pid_t	prev_pid;
	int		i;
	i = 0;
	prev_pid = 0;
	wait_status = 0;
	if(data->commands_ran == 0)
		return;
	while (i < data->commands_ran)
	{
		data->pid = waitpid(-1, &wait_status, 0);
		if (data->pid > prev_pid)
			handle_wait_stats(wait_status, &status);
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
// 		return (false);
// 	while (current)
// 	{
// 		if (current->delimiter == PIPE_SINGLE)
// 			return (true);
// 		current = current->next;
// 	}
// 	return (false);
// }

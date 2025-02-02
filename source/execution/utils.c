/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:56 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 22:13:17 by joralves         ###   ########.fr       */
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
	int		sig;

	i = 0;
	prev_pid = 0;
	wait_status = 0;
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

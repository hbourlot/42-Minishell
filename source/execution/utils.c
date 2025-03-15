/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:56 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/05 17:56:02 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_wait_stats(t_shell *data, pid_t *prev_pid, int wait_status,
		int *status)
{
	int				sig;
	static pid_t	max = 0;

	if (WIFSIGNALED(wait_status))
	{
		sig = WTERMSIG(wait_status);
		if (data->pid > *prev_pid && data->pid > max)
			*status = 128 + sig;
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(2, "\n", 1);
	}
	if (WIFEXITED(wait_status) && data->pid > *prev_pid)
		*status = WEXITSTATUS(wait_status);
	if (data->pid > *prev_pid)
		max = data->pid;
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
	status = 0;
	if (data->commands_ran == 0)
		return ;
	while (i < data->commands_ran)
	{
		data->pid = waitpid(-1, &wait_status, 0);
		handle_wait_stats(data, &prev_pid, wait_status, &status);
		prev_pid = data->pid;
		i++;
	}
	if (data->last_cmd_executed->settings.is_builtin
		&& data->last_cmd_executed->settings.builtin_id != ECHO)
	{
		return ;
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

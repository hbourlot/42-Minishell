/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/09 16:41:45 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	execute_commands(t_cmd *cmd)
{
	
}

int	execute(t_shell *data)
{
	int		i;
	int		status;
	int		wait_status;
	pid_t	prev_pid;
	
	
	i = 0;
	prev_pid = 0;
	while (i < data->nbr_of_commands)
	{
		data->pid = waitpid(-1, &wait_status, 0);
		if (WIFEXITED(wait_status) && data->pid > prev_pid)
			status = WEXITSTATUS(wait_status);
		prev_pid = data->pid;
		i++;	
	}
	//! Clear all
	return (status);
}

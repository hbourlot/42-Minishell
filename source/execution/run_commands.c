/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 18:17:04 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *command)
{
	bool	*builtin_flags[] = {&command->settings.builtin_cd,
			&command->settings.builtin_export, &command->settings.builtin_echo,
			&command->settings.builtin_env, &command->settings.builtin_unset,
			&command->settings.builtin_exit, &command->settings.builtin_pwd,
			NULL};
	int		i;

	i = 0;
	while (builtin_flags[i])
	{
		if (*builtin_flags[i])
			return (true);
		i++;
	}
	return (false);
}

bool run_builting_separately(t_shell *data, t_cmd *command)
{
	bool 	cond_1;
	bool	cond_2;
	bool	cond_3;

	cond_1 = data->nbr_of_commands == 2 && data->command->delimiter == AND_DOUBLE && !command->redir_files;
	cond_2 = data->nbr_of_commands == 1 && !command->redir_files;
	if ((cond_1 || cond_2) && is_builtin(command))
	{
		if (process_builtin(data, command) < 0)
		{
			set_error_execution(1, "Malloc", NULL, true);
			handle_error();
		}
	
		return true;
	}
	
	return false;
}



void	command_loop(t_shell *data, t_cmd *command)
{
	signal(SIGINT, SIG_IGN);
	while (command)
	{
		if (run_builting_separately(data, command))
		{
			ft_printf_error("command->path: %s\n", command->path);
			return ;
		}
		if (command->delimiter != AND_DOUBLE && command->next
			&& pipe(data->pipe_id) == -1)
			return (set_error_execution(1, "Pipe", NULL, false));
		if (do_fork(&data->pid))
			return (set_error_execution(1, "Fork", NULL, false));
		else if (data->pid == 0)
		{
			restore_signals();
			child_process(data, command);
		}
		else
		{
			if (parent_process(data, &command))
				break;
			command = command->next;
		}
	}
}

void	run_commands(t_shell *data)
{
	pid_t	*pid;

	data->prev_fd = -1;
	ft_memset(data->pipe_id, -1, sizeof(int) * 2);
	if ((data->eof))
		if (run_eof(data, &data->pid))
		{
			return ;
		}
	command_loop(data, data->command);
	set_last_status(data);
}


// echo -n oi >> file && echo -n laele
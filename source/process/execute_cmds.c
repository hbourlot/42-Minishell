/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/11 12:48:30 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


/*
	* I need to make some logic of error so i send the properly print message
	* and the properly error number but dont exit since the program needs to
	* keep working
*/
void	close_resources(int exit_code, int *pipe_id, char *msg)
{
	if (pipe_id[0] != 1)
		close(pipe_id[0]);
	if (pipe_id[1] != -1)
		close(pipe_id[1]);
	perror(msg);
	exit (exit_code);
}

static void	error_execve(t_shell *data, t_cmd *command)
{
	if (access(command->path, F_OK))
	{
		ft_putstr_fd(command->args[0], 2);
		ft_putstr_fd(": Command not found\n", STDERR_FILENO);
		cleanup_shell(data);
		exit(127);
	}
	cleanup_shell(data);
	exit (EXIT_FAILURE);
}

static int child_process(t_shell *data, t_cmd *command, int *pipe_id, int *prev_fd)
{
	if (do_dup2(command, pipe_id, prev_fd))
	{
		cleanup_shell(data);
		exit (EXIT_FAILURE);
	}
	execve(command->path, command->args, command->envp);
	error_execve(data, command);
}

static void	parent_process(t_cmd *command, int *pipe_id, int *prev_fd)
{
	if (command->next)
		close(pipe_id[1]);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (command->next)
		*prev_fd = pipe_id[0];
}

/* 
	* Need to see how to capture the pid to send properly to the main run shell
*/
static void	execute_commands(t_cmd *command, pid_t *pid)
{
	t_shell	*data;
	int		pipe_id[2];
	int		prev_fd;
	
	data = get_shell();
	while (command)
	{
		if (command->next && pipe(pipe_id) == -1)
			return (close_resources(1, pipe_id, "Pipe"));
		*pid = fork();
		if (*pid < 0)
			return (close_resources(1, pipe_id, "PID"));
		else if (pid == 0)
			child_process(data, command, pipe_id, &prev_fd);
		else
		{
			parent_process(command, pipe_id, &prev_fd);
			command = command->next;
		}
	}	
}

void	execution(t_shell *data)
{
	int		i;
	int		status;
	int		wait_status;
	pid_t	prev_pid;
	pid_t	pid;
	
	i = 0;
	prev_pid = 0;
	execute_commands(data->command, &pid);
	while (i < data->nbr_of_commands)
	{
		data->pid = waitpid(-1, &wait_status, 0);
		if (WIFEXITED(wait_status) && pid > prev_pid)
			status = WEXITSTATUS(wait_status);
		prev_pid = pid;
		i++;	
	}
	//! Clear all
	// return (status);
}

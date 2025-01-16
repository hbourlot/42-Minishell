/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 22:32:09 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/16 15:39:24 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit(exit_code);
}

static bool is_safe_to_execute(t_cmd *command)
{
	if (command->settings.only_tokens)
		return (false);
	if (command->settings.expansion && ft_strlen(command->path) == 0)
		return (false);

	return (true);
}

static void	execute_only_tokens(t_shell *data, t_cmd *command)
{
	int	code_parsing;

	code_parsing = 0;
	code_parsing = (validate_file_read_execution(command->redir_files) 
					|| validate_command_path_access(command->path));
	// ! Pretty sure dont need to validate command_path_access since its only files to handle;
	if (code_parsing)
	{
		set_error_execution(code_parsing, NULL, NULL, true);
		cleanup_shell(data);
		handle_error();
	}
	return;
}

static void	child_process(t_shell *data, t_cmd *command, int *pipe_id,
		int *prev_fd)
{
	int	code;

	if (command->settings.only_tokens)
		// Commands like: < file > file1 <file1 <file2
		execute_only_tokens(data, command);
	if (open_folders_safety(&command->fd_in, &command->fd_out, command->redir_files))
	{
		// if (!command->next) // No further commands, exit on failure
		exit(handle_error());
	}
	if (do_dup2(&command->fd_in, &command->fd_out, pipe_id, prev_fd))
	{
		cleanup_shell(data);
		exit(EXIT_FAILURE);
	}
	if (is_safe_to_execute(command)) // Execute the command, in case might be only fds to open
		execve(command->path, command->args, command->envp);
	// error_execve(data, command);
	code = validate_command_path_access(command->path);
	set_error_execution(code, NULL, NULL, true);
	handle_error();
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
static void	command_loop(t_shell *data, t_cmd *command, pid_t *pid)
{
	int		pipe_id[2];
	int		prev_fd;

	prev_fd = -1;
	ft_memset(pipe_id, -1, sizeof(int) * 2);
	if ((data->eof))
		run_eof(data, pipe_id, &prev_fd, pid);
	while (command)
	{
		// * Probably handle builting here
		if (command->next && pipe(pipe_id) == -1)
			return (set_error_execution(1, "Pipe", NULL, false));
		*pid = fork();
		if (*pid < 0)
			return (set_error_execution(1, "Fork", NULL, false));
		else if (*pid == 0)
			child_process(data, command, pipe_id, &prev_fd);
		else
		{
			parent_process(command, pipe_id, &prev_fd);
			command = command->next;
		}
	}
}

void	run_commands(t_shell *data)
{
	int		i;
	int		status;
	int		wait_status;
	pid_t	prev_pid;
	pid_t	pid;

	i = 0;
	prev_pid = 0;
	command_loop(data, data->command, &pid);
	while (i < data->nbr_of_commands)
	{
		data->pid = waitpid(-1, &wait_status, 0);
		if (WIFEXITED(wait_status) && pid > prev_pid)
			status = WEXITSTATUS(wait_status);
		prev_pid = pid;
		i++;
	}
	data->last_exit_status = status;
	//! Clear all
	// return (status);
}

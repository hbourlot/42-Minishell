/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:40:31 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/11 11:38:26 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_file *file_list)
{
	t_file	*tmp;

	while (file_list)
	{
		tmp = file_list;
		if (tmp->eof)
			free(tmp->eof);
		if (tmp->read)
			free(tmp->read);
		if (tmp->write)
			free(tmp->write);
		file_list = file_list->next;
		free(tmp);
	}
}

static void	free_command(t_cmd **command)
{
	t_cmd	*tmp;

	while (command && *command)
	{
		tmp = *command;
		free_files(tmp->rf);
		tmp->rf = NULL;
		if (tmp->input)
			free(tmp->input);
		if (tmp->args)
			free_split(tmp->args);
		if (tmp->path)
			free(tmp->path);
		if (tmp->io[0] != -1)
			close(tmp->io[0]);
		if (tmp->io[1] != -1)
			close(tmp->io[1]);
		if (tmp->input_expanded)
			free(tmp->input_expanded);
		(*command) = (*command)->next;
		free(tmp);
	}
}

void	close_fds_and_pipes(t_shell *data)
{
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (data->pipe_id[0] != -1)
		close(data->pipe_id[0]);
	if (data->pipe_id[1] != -1)
		close(data->pipe_id[1]);
}

/*
	TODO: Still need to implement this function which dont free
	TODO: 	all sources on data ⬇️
*/
void	refresh_shell_data(t_shell *data)
{
	close_fds_and_pipes(data);
	data->commands_ran = 0;
	data->nbr_of_commands = 0;
	data->pid = -1;
	data->last_cmd_executed = NULL;
	if (data->rf)
	{
		free_files(data->rf);
		data->rf = NULL;
	}
	if (data->rl)
		free_pointers(1, &data->rl);
	if (data->rl_splitted)
	{
		free_split(data->rl_splitted);
		data->rl_splitted = NULL;
	}
	free_command(&data->command);
	data->command = NULL;
	data->last_cmd_executed = NULL;
}

// * All the command->input comes from the data->input_splitted
// * so just need to free input_splitted.
void	cleanup_shell(t_shell *data)
{
	close_fds_and_pipes(data);
	if (data->rl)
		free(data->rl);
	if (data->rl_splitted)
		free_split(data->rl_splitted);
	if (data->rf)
	{
		free_files(data->rf);
		data->rf = NULL;
	}
	if (data->map)
		hashmap_free(data->map);
	if (data->envp)
		free_split(data->envp);
	if (data->env_paths)
		free_split(data->env_paths);
	free_command(&data->command);
	data->command = NULL;
}

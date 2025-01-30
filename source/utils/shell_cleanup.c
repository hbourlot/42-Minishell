/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:40:31 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/30 15:38:59 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_file *file_list)
{
	t_file	*tmp;

	while (file_list)
	{
		tmp = file_list;
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
		free_files(tmp->redir_files);
		tmp->redir_files = NULL;
		if (tmp->input)
			free(tmp->input);
		if (tmp->args)
			free_split(tmp->args);
		if (tmp->path)
			free(tmp->path);
		if (tmp->fd_in != -1) // TODO: DO I NEED??
			close(tmp->fd_in);
		if (tmp->fd_out != -1)
			close(tmp->fd_out);
		(*command) = (*command)->next;
		free(tmp);
	}
}

/*
	TODO: Still need to implement this function which dont free
	TODO: 	all sources on data ⬇️
*/
void	refresh_shell_data(t_shell *data)
{
	t_cmd	*tmp;

	data->commands_ran = 0;
	data->nbr_of_commands = 0;
	data->it_ends_with_delimiter = false;
	if (data->eof)
	{
		free_split(data->eof);
		data->eof = NULL;
	}
	if (data->readline)
		free_pointers(1, &data->readline);
	if (data->readline_splitted)
	{
		free_split(data->readline_splitted);
		data->readline_splitted = NULL;
	}
	free_command(&data->command);
	data->command = NULL;
}

// * All the command->input comes from the data->input_splitted
// * so just need to free input_splitted.
void	cleanup_shell(t_shell *data)
{
	t_cmd	*tmp;

	if (data->readline)
		free(data->readline);
	if (data->readline_splitted)
		free_split(data->readline_splitted);
	if (data->env_paths)
		free_split(data->env_paths);
	if (data->eof)
	{
		free_split(data->eof);
		data->eof = NULL;
	}
	if (data->map)
		hashmap_free(data->map);
	if (data->envp)
		free_split(data->envp);
	free_command(&data->command);
	data->command = NULL;
}

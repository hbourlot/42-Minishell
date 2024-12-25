/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:40:31 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 11:34:57 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_files(t_file *file_list)
{
	t_file *tmp;

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

/*
	TODO: Still need to implement this function which dont free 
	TODO: 	all sources on data ⬇️
*/
void	refresh_shell_data(t_shell *data)
{
	t_cmd	*tmp;

	if (data->input_splitted)
	{
		free_split(data->input_splitted);
		data->input_splitted = NULL;
	}
	while (data->command)
	{
		tmp = data->command;
		free_files(tmp->file_list);
		tmp->file_list = NULL;
		if (tmp->input)
			free(tmp->input);
		if (tmp->args)
			free_split(tmp->args);
		if (tmp->path)
			free(tmp->path);
		data->command = data->command->next;
		free(tmp);
	}
	data->command = NULL;
}

// * All the command->input comes from the data->input_splitted
// * so just need to free input_splitted.
void	cleanup_shell(t_shell *data)
{
	t_cmd	*tmp;

	if (data->input_splitted)
		free_split(data->input_splitted);
	if (data->env_paths)
		free_split(data->env_paths);
	while (data->command)
	{
		tmp = data->command;
		free_files(tmp->file_list);
		if (tmp->input)
			free(tmp->input);
		if (tmp->args)
			free_split(tmp->args);
		if (tmp->path)
			free(tmp->path);
		data->command = data->command->next;
		free(tmp);
	}
	data->command = NULL;
}

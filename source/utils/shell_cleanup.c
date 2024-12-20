/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:40:31 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/20 21:41:39 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		free_split(data->input_splitted);
		data->input_splitted = NULL;
	}
	// if (data->env_paths)
	// {
	// 	free_split(data->env_paths);
	// 	data->env_paths = NULL;
	// }
	while (data->command)
	{
		tmp = data->command;
		if (tmp->args)
			free_split(tmp->args);
		if (tmp->path)
			free(tmp->path);
		data->command = data->command->next;
		free(tmp);
	}
	data->command = NULL;
}

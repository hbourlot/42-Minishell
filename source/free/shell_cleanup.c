/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:40:31 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/12 17:03:43 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


// * All the command->input comes from the data->input_splitted
// * so just need to free input_splitted.
void	cleanup_shell(t_shell *data)
{
	t_cmd *tmp;
	
	if (data->input_splitted)
	{
		free_split(data->input_splitted);
		data->input_splitted = NULL;
	}
	data->input_splitted = NULL;
	while(data->command)
	{
		tmp = data->command;
		if (tmp->args)
			free_split(tmp->args);
		data->command = data->command->next;
		free(tmp);
	}
	data->command = NULL;
}

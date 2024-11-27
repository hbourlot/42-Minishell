/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:40:31 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/27 17:39:01 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	cleanup_shell(t_shell **data)
{
	t_cmd *tmp;
	
	if ((*data)->input_splitted)
		free_split((*data)->input_splitted);
	(*data)->input_splitted = NULL;
	while((*data)->command)
	{
		tmp = (*data)->command;
		(*data)->command = (*data)->command->next;
		free(tmp);
	}
	(*data)->command = NULL;
	*data = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:22 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/26 20:09:56 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void *error_create_cmds(t_cmd **cmd)
{
	t_cmd *tmp;

	tmp = *cmd;
	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free(tmp);
	}
	*cmd = NULL;
	return (NULL);
}

t_cmd	*create_cmds(char **cmds_splitted)
{
	int		i;
	t_cmd 	*command;
	t_cmd	*tmp;
	int		nbr_of_commands;
	
	nbr_of_commands = split_length(cmds_splitted);
	command = ft_calloc(1 , sizeof(t_cmd));
	if (!command)
		return (free_split(cmds_splitted), NULL);
	i = 0;
	tmp = command;
	while (i < nbr_of_commands)
	{
		tmp->next = ft_calloc(1 , sizeof(t_cmd));
		if (!tmp->next)
			return (error_create_cmds(&command));
		tmp = tmp->next;
		i++;
	}
	return (command);
}

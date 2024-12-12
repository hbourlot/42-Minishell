/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:51:22 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/30 16:35:16 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void *free_cmd_list_on_error(t_cmd **cmd)
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

/// @brief Creates a linked list of commands from a split command array.
/// @param cmds_splitted An array of strings, where each string represents a command or argument.
/// @return A pointer to the head of the linked list of commands, or NULL if memory allocation fails.
t_cmd	*create_command_list(char **cmds_splitted)
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
	while (i < (nbr_of_commands - 1))
	{
		tmp->next = ft_calloc(1 , sizeof(t_cmd));
		if (!tmp->next)
			return (free_cmd_list_on_error(&command));
		tmp = tmp->next;
		i++;
	}
	return (command);
}

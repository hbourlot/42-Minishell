/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/05 20:50:39 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void *free_cmd_list_on_error(t_cmd *cmd) // ! Need manage this function in name and place to keep it
{
	t_cmd *tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	return (NULL);
}

t_cmd	*create_cmd(char *command_input, char *envp[])
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, sizeof(t_cmd));
	tmp->command_input = command_input;
	tmp->envp = envp;

	return (tmp);
}

int	init_command(char *input, const char *delimiters[])
{
	t_cmd	*cmd;
	t_cmd	*current;
	char	**split_input;
	int		i;

	i = 0;
	split_input = split_by_multiple_tokens(input, delimiters);
	if (!split_input)
		return (-1); // ! Error managing here
	cmd = create_cmd(split_input[i++]);
	if (!cmd)
		return (free(split_input), -1);
	get_shell()->command = cmd;
	current = cmd;
	while (split_input[i])
	{
		current->next = create_cmd(split_input[i++]);
		if (!current->next)
		{
			free_cmd_list_on_error(cmd);
			return (free_split(split_input), -1); // ! Also need to free all previously struct command;		
		}
		current = current->next;
	}
	return (0);
}


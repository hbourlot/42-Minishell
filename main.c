/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/26 20:33:05 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


static void error_create_cmds(t_cmd **cmd)
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
}

t_cmd	*create_cmds(char *cmd_line)
{
	int		i;
	char 	**cmds_split;
	t_cmd 	*command;
	t_cmd	*tmp;
	int		nbr_of_commands;
	
	
	cmds_split = ft_split(cmd_line, '|');
	nbr_of_commands = 0;
	while (cmds_split[nbr_of_commands])
		nbr_of_commands++;
	command = ft_calloc(1 , sizeof(t_cmd));
	if (!command)
		return (NULL);
	i = 0;
	command->pre_command = cmds_split[i++];
	tmp = command;
	while (i < nbr_of_commands)
	{
		tmp->next = ft_calloc(1 , sizeof(t_cmd));
		if (!tmp->next)
			error_create_cmds(&command);
		tmp->next->pre_command = cmds_split[i];
		tmp = tmp->next;
		i++;
	}
	return (command);
}


void	free_shell(t_shell *data)
{
	free_split(data->cmds_splitted);
}

t_shell *instance_shell()
{
	static t_shell data;
	return (&data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd		*command;
	char		*buffer;

	char *cmd_line = get_next_line(0);
	instance_shell()->cmds_splitted = ft_split(cmd_line, '|');

	printf("%s\n", instance_shell()->cmds_splitted[0]);
	
	// data.cmds_splitted = ft_split(cmd_line, "|");
	// if (!data.cmds_splitted)
	// 	return (free_shell(&data), -1); // ! Need better management here.
		
	// command = create_cmds(data.cmds_splitted);
	// if (!command)
	// 	return (ft_putstr_fd("Error creating commands.\n", 2), 1);
	


	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:18:25 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/27 17:31:22 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void	debug_command_precommand(t_shell *data)
{
	t_cmd	*tmp;
	int	i;

	i = 1;
	tmp = data->command;
	while (tmp)
	{
		printf("Command->pre_command [%d]: %s\n", i++, tmp->pre_command);
		tmp = tmp->next;
	}
}

void	debug_command_args(t_shell *data)
{
	t_cmd	*tmp;
	int	i;
	int	j;
	
	i = 1;
	tmp = data->command;
	while (tmp)
	{
		j = 0;
		if (tmp->args)
		{
			while(tmp->args[j])
			{
				printf("Command->args [%d][%d]: %s\n", i, j + 1, tmp->args[j]);
				j++;
			}
		}
		else
		{
			printf("args == NULL\n");
			break;
		}
		i++;
		tmp = tmp->next;
	}	
}

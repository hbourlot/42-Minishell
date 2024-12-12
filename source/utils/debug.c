/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:18:25 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/12 14:41:45 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "minishell.h"

void	debug_command_input(t_shell *data)
{
	t_cmd	*tmp;
	int	i;

	i = 1;
	tmp = data->command;
	while (tmp)
	{
		printf("Command->pre_command [%d]: %s\n", i++, tmp->command_input);
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

void	debug_command_path(t_shell *data)
{
	int		i;
	t_cmd	*tmp;

	i = 1;
	tmp = data->command;
	while (tmp)
	{
		if (tmp->path)
			printf("Command->path [%d]: %s\n", i, tmp->path);
		else
			printf("Command->path [%d]: has no path", i);
		i++;
		tmp = tmp->next;
	}
}

void error_msg(void)
{
	ft_putstr_fd("Error\n", 2);
}

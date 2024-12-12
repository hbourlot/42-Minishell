/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:26:50 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/12 13:03:43 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_envp(t_shell *data)
{
	int			i;

	i = 0;
	if (!data->envp || !*data->envp)
	{
		data->env_paths = NULL;
		return ;
	}
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == CMP_OK)
		{
			if (ft_strlen(data->envp[i] + 5) == 0)
				data->env_paths = NULL;
			else
				data->env_paths = ft_split(data->envp[i] + 5, ':');
			break ;
		}
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:26:50 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/11 21:27:16 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_envp(t_shell *data)
{
	int			i;
	t_env_info	*info;

	info = &data->env_info;
	i = 0;
	if (!data->envp || !*data->envp)
	{
		info->has_envp = false;
		return ;
	}
	info->has_envp = true;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == CMP_OK)
		{
			info->has_path = true;
			if (ft_strlen(data->envp[i] + 5) == CMP_OK)
				info->is_path_empty = true;
			else
				info->path = data->envp[i] + 5;
			break ;
		}
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:16:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/30 20:58:26 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	initialize_environment_paths(t_shell *data)
// {
// 	int			i;
// 
// 	i = 0;
// 	if (!data->envp || !*data->envp)
// 	{
// 		data->env_paths = NULL;
// 		return (SUCCESS);
// 	}
// 	while (data->envp[i])
// 	{
// 		if (ft_strncmp(data->envp[i], "PATH=", 5) == CMP_OK)
// 		{
// 			if (ft_strlen(data->envp[i] + 5) == 0)
// 				data->env_paths = NULL;
// 			else
//             {
// 				data->env_paths = ft_split(data->envp[i] + 5, ':');
//                 if (!data->env_paths)
//                     return (ERROR);
//             }
// 			break ;
// 		}
// 		i++;
// 	}
//     return (SUCCESS);
// }

int	initialize_environment_paths(t_shell *data)
{
	char *path;

	path = hashmap_search(data->map, "PATH");
	if (!data->envp || !data->envp || !path)
	{
		data->env_paths = NULL;
		return (SUCCESS);
	}
	data->env_paths = ft_split(path, ':');
	if (!data->env_paths)
		return (ERROR);
	return (SUCCESS);
}
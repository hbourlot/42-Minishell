/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:16:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/16 00:34:11 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	initialize_environment_paths(t_shell *data)
// {
// 	int			i;

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

int    initialize_environment_paths(t_shell *data)
{
    int        i;
    char    *path;

    i = 0;
    path = getenv("PATH");
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
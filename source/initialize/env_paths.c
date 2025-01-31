/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:16:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/31 18:06:27 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_environment_paths(t_shell *data)
{
	char *path;
	if (data->env_paths)
		free_split(data->env_paths);
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
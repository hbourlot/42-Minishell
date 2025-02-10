/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:16:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 16:54:14 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_environment_paths(t_shell *data)
{
	char	*path;

	if (data->env_paths)
		free_split(data->env_paths);
	path = hashmap_search(data->map, "PATH");
	if (!data->envp || !data->envp || !path)
	{
		data->env_paths = NULL;
		return ;
	}
	data->env_paths = ft_split(path, ':');
	if (!data->env_paths)
		handle_error(E_MALLOC, NULL, __func__);
}

/// @brief Updates environment variables and paths.
/// @param data The shell structure with mappings.
/// @return SUCCESS on update, ERROR if malloc fails.
void	update_envp_and_envpath(t_shell *data)
{
	hashmap_to_env_array(data, data->map);
	initialize_environment_paths(data);
}

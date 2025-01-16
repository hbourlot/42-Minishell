/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:38:12 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/16 00:43:53 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable_path(char *executable, char **env_paths,
		bool *only_executable)
{
	int		i;
	char	*partial_path;
	char	*full_path;

	i = 0;
	while (ft_strlen(executable) > 0 && env_paths[i])
	{
		partial_path = ft_strjoin(env_paths[i], "/");
		if (!partial_path)
			return (NULL);
		full_path = ft_append_and_free(partial_path, executable);
		if (!full_path)
			return (free(partial_path), NULL);
		if (access(full_path, F_OK) == CMP_OK)
			return (full_path);
		if (!env_paths[i + 1])
		{
			*only_executable = true;
			return (free(full_path), NULL);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *command_str, char **env_paths)
{
	char	*executable;
	char	**command_splitted;
	bool	only_executable;
	int		i;
	char	*path;

	executable = NULL;
	only_executable = false;
	executable = ft_strdup(command_str);
	if (!executable)
	{
		set_error_initialize(1, "Malloc", __func__, true);
		return (NULL);
	}
	if (!*env_paths)
		return (executable);
	if (ft_strlen(executable) > 0 && ft_strchr(executable, '/'))
		return (executable);
	path = find_executable_path(executable, env_paths, &only_executable);
	if (only_executable)
		return (executable);
	free(executable);
	return (path);
}

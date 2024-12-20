/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:38:12 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/18 21:00:28 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable_path(char *executable, char **env_paths)
{
	int		i;
	char 	*pre_path;
	char	*path;

	i = 0;
	while (env_paths[i])
	{
		pre_path = ft_strjoin(env_paths[i], "/");
		if (!pre_path)
			return (NULL);
		path = ft_append_and_free(pre_path, executable);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == CMP_OK || !env_paths[i + 1])
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char *get_path(char *input, char **env_paths)
{
	char	*executable;
	char	**command_splitted;
	int		i;
	char	*path;

	command_splitted = ft_split(input, ' ');
	if (!command_splitted)
		return (NULL);
	executable = ft_strdup(command_splitted[0]);
	if (!executable)
		return (free_split(command_splitted), NULL);
	free_split(command_splitted);
	if (ft_strchr(executable, '/'))
		return (executable);
	path = find_executable_path(executable, env_paths);
	free(executable);
	return (path);	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:52:16 by joralves          #+#    #+#             */
/*   Updated: 2025/02/01 23:20:19 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hashmap_free(t_hashmap *map)
{
	int			i;
	t_hashnode	*current;
	t_hashnode	*temp;

	i = 0;
	if (!map)
		return ;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		while (current)
		{
			temp = current;
			current = current->next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
		i++;
	}
}

t_hashmap	*create_map(void)
{
	static t_hashmap	map;

	return (&map);
}
int	update_shell_lvl(t_hashmap *map)
{
	const char	*key = "SHLVL";
	char		*temp;
	int			temp_lvl;
	char		*temp_value;

	temp = hashmap_search(map, (char *)key);
	if (!temp)
		return (-1);
	temp_lvl = ft_atoi(temp);
	temp_lvl++;
	temp_value = ft_itoa(temp_lvl);
	if (!temp_value)
		return (ERROR);
	if (hashmap_insert(map, (char *)key, temp_value) == ERROR)
		return (free(temp_value), ERROR);
	return (free(temp_value), 0);
}

/// @brief Imports environment variables from an array into a hashmap.
/// @param map The hashmap to store the environment variables as key-value pairs.
/// @param envp The array of environment variables in "KEY=VALUE" format.
/// @return 0 on success, -1 on memory allocation or insertion failure.
int	import_env_to_hashmap(t_hashmap *map, char *envp[])
{
	int		i;
	char	*delimeter;
	size_t	len;
	char	*key;

	i = 0;
	while (envp[i])
	{
		delimeter = ft_strchr(envp[i], '=');
		len = delimeter - envp[i];
		key = ft_substr(envp[i], 0, len);
		if (!key)
			return (ERROR);
		if (hashmap_insert(map, key, delimeter + 1) == -1)
			if (hashmap_insert(map, key, delimeter + 1) == -1)
				return (free(key), ERROR);
		free(key);
		i++;
	}
	if (update_shell_lvl(map) == ERROR)
		return (ERROR);
	return (0);
}

/// @brief Converts a hashmap of environment variables into an environment array.
/// @param data The shell structure where the environment array will be stored.
/// @param map The hashmap containing the environment variables as key-value pairs.
/// @return 0 on success, -1 on memory allocation failure.
int	hashmap_to_env_array(t_shell *data, t_hashmap *map)
{
	int			i;
	t_hashnode	*current;
	size_t		idx;

	if (data->envp)
		free_split(data->envp);
	data->envp = ft_calloc(map->total_size + 1, sizeof(char *));
	if (!data->envp)
		return (ft_printf_error("Malloc fail %s\n", __func__), ERROR);
	i = 0;
	idx = 0;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		while (current)
		{
			if (current->key && current->value)
			{
				data->envp[idx] = ft_strjoin_char(current->key, current->value,
						'=');
				if (!data->envp[idx])
					return (ft_printf_error("Malloc fail %s\n", __func__),
						ERROR);
				idx++;
			}
			current = current->next;
		}
		i++;
	}
	return (0);
}

/// @brief Updates the environment variables and paths in the shell structure.
/// @param data The shell structure containing environment mappings and state.
/// @return SUCCESS on successful update, ERROR if malloc fails.
int	update_envp_and_envpath(t_shell *data)
{
	if (hashmap_to_env_array(data, data->map) == ERROR)
		return (ERROR);
	if (initialize_environment_paths(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

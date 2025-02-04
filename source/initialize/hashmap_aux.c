/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:52:16 by joralves          #+#    #+#             */
/*   Updated: 2025/02/04 16:47:18 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	update_shell_lvl(t_hashmap *map)
// {
// 	char		*temp;
// 	int			temp_lvl;
// 	char		*temp_value;

// 	temp = hashmap_search(map, "SHLVL");
// 	if (!temp)
// 		return (-1);
// 	temp_lvl = ft_atoi(temp);
// 	temp_lvl++;
// 	temp_value = ft_itoa(temp_lvl);
// 	if (!temp_value)
// 		return (ERROR);
// 	if (hashmap_insert(map, "SHLVL", temp_value) == ERROR)
// 		return (free(temp_value), ERROR);
// 	return (free(temp_value), 0);
// }

/// @brief Imports environment variables into a hashmap.
/// @param map The hashmap to store key-value pairs.
/// @param envp The array of variables in "KEY=VALUE" format.
/// @return 0 on success, -1 on allocation or insertion failure.
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
			return (free(key), ERROR);
		free(key);
		i++;
	}
	// if (update_shell_lvl(map) == ERROR)
	// 	return (ERROR);
	return (0);
}

static int	populate_env_array(char **envp, t_hashnode *current, size_t *idx)
{
	while (current)
	{
		if (current->key && current->value)
		{
			envp[*idx] = ft_strjoin_char(current->key, current->value, '=');
			if (!envp[*idx])
				return (ERROR);
			(*idx)++;
		}
		current = current->next;
	}
	return (0);
}

/// @brief Converts a hashmap into an environment array.
/// @param data The shell structure to store the array.
/// @param map The hashmap with environment variables.
/// @return 0 on success, -1 on allocation failure.
int	hashmap_to_env_array(t_shell *data, t_hashmap *map)
{
	int			i;
	t_hashnode	*current;
	char		**envp;
	size_t		idx;

	idx = 0;
	if (data->envp)
	{
		free_split(data->envp);
		data->envp = NULL;
	}
	envp = ft_calloc(map->total_size + 1, sizeof(char *));
	if (!envp)
		return (ERROR);
	i = 0;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		if (populate_env_array(envp, current, &idx) == ERROR)
			return (ERROR);
		i++;
	}
	data->envp = envp;
	return (0);
}

char	*hashmap_search(t_hashmap *map, char *key)
{
	size_t		index;
	t_hashnode	*current;

	index = hash(key);
	current = map->slots[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:52:16 by joralves          #+#    #+#             */
/*   Updated: 2025/01/23 15:02:23 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hashmap_display(t_hashmap *map)
{
	t_hashnode	*current;
	int			i;

	i = 0;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		while (current)
		{
			printf("%d %s=%s\n", i, current->key, current->value);
			current = current->next;
		}
		i++;
	}
}

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

int	import_env_to_hashmap(t_hashmap *map, char *envp[])
{
	int		i;
	char	*delimeter;
	size_t	len;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		delimeter = ft_strchr(envp[i], '=');
		len = delimeter - envp[i];
		key = ft_substr(envp[i], 0, len);
		if (!key)
			return (-1);
		value = ft_substr(delimeter, 1, ft_strlen(delimeter) + 1);
		if (!value)
			return (free(key), -1);
		if (hashmap_insert(map, key, value) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	hashmap_to_env_array(t_shell *data, t_hashmap *map)
{
	int			i;
	t_hashnode	*current;
	size_t		idx;

	data->envp = ft_calloc(map->total_size + 1, sizeof(char *));
	if (!data->envp)
		return (-1);
	i = 0;
	idx = 0;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		while (current)
		{
			data->envp[idx] = ft_strjoin_char(current->key, current->value,
					'=');
			if (!data->envp[idx])
				return (-1);
			idx++;
			current = current->next;
		}
		i++;
	}
	return (0);
}

int	update_envp_and_envpath(t_shell *data)
{
	if (hashmap_to_env_array(data, data->map) == ERROR)
		return (ERROR);
	if (initialize_environment_paths(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

// Update funtion, must update envp, and env_paths, for easy things
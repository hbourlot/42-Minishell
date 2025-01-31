/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:48:06 by joralves          #+#    #+#             */
/*   Updated: 2025/01/31 18:28:46 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	hash(char *key)
{
	int		i;
	size_t	hash_value;

	hash_value = 0;
	i = 0;
	while (key[i])
	{
		hash_value += key[i] * (i + 1);
		i++;
	}
	return (hash_value % HASHMAP_SIZE);
}

static t_hashnode	*find_node(t_hashmap *map, char *key)
{
	size_t		index;
	t_hashnode	*current;

	index = hash(key);
	current = map->slots[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	hashmap_insert(t_hashmap *map, char *key, char *value)
{
	size_t		index;
	t_hashnode	*current;
	t_hashnode	*new_node;

	current = find_node(map, key);
	if (current)
	{
		free(current->value);
		current->value = ft_strdup(value);
		if (!current->value)
			return (ERROR);
		return (0);
	}
	index = hash(key);
	new_node = malloc(sizeof(t_hashnode));
	if (!new_node)
		return (ERROR);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), ERROR);
	new_node->value = ft_strdup(value);
	if (!new_node->value && value)
		return (free(new_node->key), free(new_node), ERROR);
	new_node->next = map->slots[index];
	map->slots[index] = new_node;
	map->total_size += 1;
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

void	hashmap_delete(t_hashmap *map, char *key)
{
	size_t		index;
	t_hashnode	*prev;
	t_hashnode	*current;

	index = hash(key);
	prev = NULL;
	current = map->slots[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				map->slots[index] = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

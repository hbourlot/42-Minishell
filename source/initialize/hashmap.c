/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:48:06 by joralves          #+#    #+#             */
/*   Updated: 2025/02/06 12:43:10 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	hash(char *key)
{
	int		i;
	size_t	hash_value;

	hash_value = 0;
	i = 0;
	while (key[i])
	{
		hash_value = hash_value * 31 + key[i];
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

static int	new_hasnode(t_hashmap *map, char *key, char *value)
{
	size_t		index;
	t_hashnode	*new_node;

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

int	hashmap_insert(t_hashmap *map, char *key, char *value)
{
	t_hashnode	*current;

	current = find_node(map, key);
	if (current)
	{
		free(current->value);
		current->value = ft_strdup(value);
		if (!current->value && value)
			return (ERROR);
		return (0);
	}
	if (new_hasnode(map, key, value) == ERROR)
		return (ERROR);
	return (0);
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

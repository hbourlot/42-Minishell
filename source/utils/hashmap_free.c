/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:05:07 by joralves          #+#    #+#             */
/*   Updated: 2025/02/10 16:06:24 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hashnode_free(t_hashnode *current)
{
	t_hashnode	*temp;

	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	hashmap_free(t_hashmap *map)
{
	int			i;
	t_hashnode	*current;

	i = 0;
	if (!map)
		return ;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		hashnode_free(current);
		i++;
	}
}

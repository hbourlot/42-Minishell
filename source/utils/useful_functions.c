/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:17:42 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/06 18:17:18 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_spaces(char **src)
{
	if (!src || !*src)
		return;
	while (**src && **src == ' ')
		(*src)++;
}

void skip_character_by_idx(char *src, char c, int *i)
{
	if (!src)
		return;
	while (src[*i] && src[*i] == c)
		(*i)++;
}

void	skip_character_diff_by_idx(char *src, char c, int *i)
{
	if (!src)
		return;
	while (src[*i] && src[*i] != c)
		(*i)++;
}

void	replace_characters(char *src, char to_take, char to_put)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		if (src[i] == to_take)
			src[i] = to_put;
		i++;
	}
}

void	restore_original_characters(char **src)
{
	const char tk[] = {REP_SPACE, REP_SINGLE_QUOTE, REP_DOUBLE_QUOTE, '\0'};
	const char to_set[] = {' ', '\'', '"'};
	int	i;
	int	j;

	i = 0;
	while (src && (*src)[i])
	{
		j = 0;
		while (tk[j])
		{
			if ((*src)[i] == tk[j])
				(*src)[i] = to_set[j];
			j++;
		}
		i++;
	}
}

static t_hashnode	*sorted_insert(t_hashnode *sorted, t_hashnode *new_node)
{
	t_hashnode	*current;

	if (!new_node)
		return (sorted);
	if (!sorted || ft_strcmp(new_node->key, sorted->key) < 0)
	{
		new_node->next = sorted;
		return (new_node);
	}
	current = sorted;
	while (current->next && ft_strcmp(current->next->key, new_node->key) < 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (sorted);
}

void	insertion_sort(t_hashnode **head)
{
	t_hashnode	*sorted;
	t_hashnode	*current;
	t_hashnode	*next;

	if (!head || !*head || !(*head)->next)
		return ;
	sorted = NULL;
	current = *head;
	while (current)
	{
		next = current->next;
		current->next = NULL;
		sorted = sorted_insert(sorted, current);
		current = next;
	}
	*head = sorted;
}
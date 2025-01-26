/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:17:42 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/23 13:57:13 by hbourlot         ###   ########.fr       */
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

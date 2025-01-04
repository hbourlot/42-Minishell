/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 10:46:44 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/02 23:32:45 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_occurrence(char *src, const char *here_docs[])
{
	int	times;

	times = 0;
	while(src && *src)
	{
		src = ft_strstr_any(src, here_docs);
		if (src)
		{
			src += 2;
			times++;
		}
	}
	return (times);
}

static int	get_first_here_doc_occurrence(char **src, const char *hd[])
{
	(*src) = ft_strstr_any((*src), hd);
	if (!(*src))
		return (-1);
	return (0);
}

static void	skip_spaces(char **src)
{
	while (*(*src) && *(*src) == ' ')
		(*src)++;
}

static int	allocate_memory(char ***eof, char **src, const char *hd[], int *idx)
{
	int	i;
	
	i = 0;
	while ((*src)[i] && ft_strcmp(&(*src)[i], hd[0]) && (*src)[i] != ' ')
		i++;
	(*eof)[*idx] = ft_substr((*src), 0, i);
	if (!(*eof)[*idx])
	{
		return (free_split((*eof)), -1);
	}
	(*eof)[*idx] = ft_append_and_free((*eof)[*idx], "\n");
	if (!(*eof)[*idx])
		return (free_split((*eof)), -1);
	(*idx)++;
	(*src) += i;
	return (0);
}

int	initialize_here_doc(char *input_splitted, char ***eof)
{
	const char 	*here_doc[] = {"<<", NULL};
	char		*src;
	int			idx;
	int			occurrence_times;
	
	occurrence_times = count_occurrence(input_splitted, here_doc);
	if (occurrence_times == 0)
		return (0);
	(*eof) = malloc(sizeof(char *) * (occurrence_times + 1));
	if (!*eof)
		return (-1);
	idx = 0;
	src = input_splitted;
	while (src && *src)
	{
		if (get_first_here_doc_occurrence(&src, here_doc))
			break;
		src += 2; // length of here_doc
		skip_spaces(&src);
		if (allocate_memory(eof, &src, here_doc, &idx))
			return (-1);
	}
	(*eof)[idx] = NULL;
	return (0);
}


		// i = 0;
		// while (src[i] && ft_strcmp(&src[i], hd[0]) && src[i] != ' ')
		// 	i++;
		// (*eof)[idx] = ft_substr(src, 0, i);
		// if (!(*eof)[idx])
		// 	return (free_split((*eof)), -1);
		// idx++;
		// src += i;
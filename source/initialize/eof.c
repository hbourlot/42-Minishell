/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 10:46:44 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/12 12:51:44 by hbourlot         ###   ########.fr       */
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

static int	get_first_token_occurrence(char **src, const char *token[])
{
	(*src) = ft_strstr_any((*src), token);
	if (!(*src))
		return (-1);
	return (0);
}

static int	allocate_memory(char ***eof, char **src, const char *hd[], int *idx)
{
	int	i;
	
	i = 0;
	while ((*src)[i] && ft_strcmp(&(*src)[i], hd[0]) && (*src)[i] != ' ')
		i++;
	(*eof)[*idx] = ft_substr((*src), 0, i);
	if (!(*eof)[*idx])
		return (free_split((*eof)), -1);
	(*eof)[*idx] = ft_append_and_free((*eof)[*idx], "\n");
	if (!(*eof)[*idx])
		return (free_split((*eof)), -1);
	(*idx)++;
	(*src) += i;
	return (0);
}

int	initialize_eof(char *data_readline, char ***data_eof)
{
	const char 	*token[] = {"<<", NULL};
	char		*src;
	int			idx;
	int			occurrence_times;

	occurrence_times = count_occurrence(data_readline, token);
	if (occurrence_times == 0)
		return (0);
	(*data_eof) = malloc(sizeof(char *) * (occurrence_times + 1));
	if (!*data_eof)
		return (-1);
	idx = 0;
	src = data_readline;
	while (src && *src)
	{
		if (get_first_token_occurrence(&src, token))
			break;
		src += 2; // length of here_doc
		skip_spaces(&src);
		if (allocate_memory(data_eof, &src, token, &idx))
			return (-1);
	}
	(*data_eof)[idx] = NULL;
	return (0);
}
// int	initialize_eof(char **readline_splitted, char ***data_eof)
// {
// 	const char 	*token[] = {"<<", NULL};
// 	char		*src;
// 	int			idx;
// 	int			occurrence_times;
// 	int			i;

// 	i = 0;
// 	occurrence_times = 0;
// 	while (readline_splitted[i])
// 	{
// 		occurrence_times += count_occurrence(readline_splitted[i], token);
// 		i++;
// 	}
// 	if (occurrence_times == 0)
// 		return (0);
// 	(*data_eof) = malloc(sizeof(char *) * (occurrence_times + 1));
// 	if (!*data_eof)
// 		return (-1);
// 	idx = 0;
// 	i = 0;
// 	while (readline_splitted[i])
// 	{
// 		src = readline_splitted[i];
// 		while (src && *src)
// 		{
// 			if (get_first_token_occurrence(&src, token))
// 				break;
// 			src += 2; // length of here_doc
// 			skip_spaces(&src);
// 			if (allocate_memory(data_eof, &src, token, &idx))
// 				return (-1);
// 		}
// 		i++;
// 	}
// 	(*data_eof)[idx] = NULL;
// 	return (0);
// }


//echo oi << file << file1 | ls << file
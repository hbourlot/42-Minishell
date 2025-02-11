/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 10:46:44 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/11 10:14:53 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_occurrence(char *src)
{
	int			idx;
	int			times;
	bool		in_quotes;
	const char	*tokens[] = {"<<", NULL};

	times = 0;
	in_quotes = false;
	while (src && *src)
	{
		if (*src && (*src == REP_SINGLE_QUOTE || *src == REP_DOUBLE_QUOTE))
			in_quotes = !in_quotes;
		if (!in_quotes && find_string_match(src, tokens, &idx) == OK)
			times++;
		src++;
	}
	return (times);
}

static int	allocate_eof(char **data_eof, char **data_readline, int *idx)
{
	int	start;
	int	end;

	start = -1;
	end = -1;
	get_redirect_complement(*data_readline, &start, &end, 2);
	if (start == -1 || end == -1)
		return (-1);
	data_eof[*idx] = ft_substr(*data_readline, start, end - start);
	data_eof[*idx] = ft_append_and_free(data_eof[*idx], "\n");
	if (!data_eof[*idx])
		return (-1);
	(*idx)++;
	return (0);
}

int	allocate_data_eof(char *data_readline, char ***data_eof)
{
	int	occurrence_times;

	occurrence_times = count_occurrence(data_readline);
	if (occurrence_times == 0)
		return (0);
	(*data_eof) = malloc(sizeof(char *) * (occurrence_times + 1));
	if (!*data_eof)
		return (-1);
	return (1);
}

int	initialize_eof(char *data_readline, char ***data_eof)
{
	int	idx;
	int	in_quotes;
	int	alloc_status;

	alloc_status = allocate_data_eof(data_readline, data_eof);
	if (alloc_status <= 0)
		return (alloc_status);
	idx = 0;
	in_quotes = false;
	while (data_readline && *data_readline)
	{
		if (*data_readline && (*data_readline == REP_SINGLE_QUOTE
				|| *data_readline == REP_DOUBLE_QUOTE))
			in_quotes = !in_quotes;
		else if (!in_quotes && ft_strncmp(data_readline, "<<", 2) == CMP_OK)
		{
			if (allocate_eof(*data_eof, &data_readline, &idx) < 0)
				return (-1);
		}
		data_readline++;
	}
	(*data_eof)[idx] = NULL;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 10:46:44 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/21 13:56:48 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_rf_to_list(t_shell *data, t_file *rf_new)
{
	t_file	*last;

	if (!data->rf)
		data->rf = rf_new;
	else
	{
		last = data->rf;
		while (last->next)
			last = last->next;
		last->next = rf_new;
	}
}

static int	allocate_eof(t_shell *data, int i)
{
	int		j;
	t_file	*new;
	int		p[2];

	j = 2;
	get_redirect_complement(&data->rl[i], &p[0], &p[1], 2);
	if (p[0] == -1 || p[1] == -1)
		return (0);
	new = ft_calloc(1, sizeof(t_file));
	if (!new)
		return (-1);
	new->eof = ft_substr(&data->rl[i], p[0], p[1] - p[0]);
	if (!new->eof)
		return (free(new), -1);
	truncate_character(new->eof, REP_DQ);
	truncate_character(new->eof, REP_SQ);
	replace_characters(new->eof, REP_PIPE, '|');
	replace_characters(new->eof, REP_PIPE, '&');
	while (data->rl[i + j] && data->rl[i + j] == REP_SPACE)
		j++;
	if (data->rl[i + j] == REP_SQ || data->rl[i + j] == REP_DQ)
		new->in_quotes = true;
	add_rf_to_list(data, new);
	return (0);
}

int	initialize_eof(t_shell *data)
{
	int	i;
	int	idx;
	int	in_quotes;

	i = 0;
	idx = 0;
	in_quotes = false;
	while (data->rl && data->rl[i])
	{
		if (data->rl[i] && (data->rl[i] == REP_SQ || data->rl[i] == REP_DQ))
			in_quotes = !in_quotes;
		else if (!in_quotes && ft_strncmp(&data->rl[i], "<<", 2) == CMP_OK)
		{
			if (allocate_eof(data, i) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

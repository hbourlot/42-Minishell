/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_sq_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:44:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/14 15:29:31 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_occurrence(int *occurrence, int *idx)
{
	if (occurrence[0] == -1)
		occurrence[0] = *idx;
	else if (occurrence[1] == -1)
		occurrence[1] = *idx;
}

static void	identify_idx_of_occurrences(char *readline, char *in_quotes,
		int *occurrence, int *idx)
{
	if (!readline[*idx])
		return;
	if (readline[*idx] == '\'' && *in_quotes != '"')
	{
		*in_quotes = '\'';
		set_occurrence(occurrence, idx);
	}
	else if (readline[*idx] == '"' && *in_quotes != '\'')
	{
		*in_quotes = '"';
		set_occurrence(occurrence, idx);
	}
	(*idx)++;
	if (occurrence[0] != -1 && occurrence[1] != -1)
		return;
	identify_idx_of_occurrences(readline, in_quotes, occurrence, idx);
}

static void	replace_non_literal_spaces(char **input)
{
	int		i;
	bool	in_quotes;

	in_quotes = false;
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == REP_DOUBLE_QUOTE || (*input)[i] == REP_SINGLE_QUOTE)
			in_quotes = !in_quotes;
		else if ((*input)[i] == ' ' && !in_quotes)
			(*input)[i] = REP_SPACE;
		i++;
	}
}

void	identify_and_replace_sq_tokens(char **input)
{
	int idx;
	char in_quotes;
	int occurrence[2];
	char tag;

	idx = 0;
	in_quotes = '\0';
	ft_memset(occurrence, -1, 8);
	identify_idx_of_occurrences((*input), &in_quotes, occurrence, &idx);
	while (occurrence[0] != -1 && occurrence[1] != -1)
	{
		if (in_quotes == '\'')
			tag = REP_SINGLE_QUOTE;
		else if (in_quotes == '"')
			tag = REP_DOUBLE_QUOTE;

		(*input)[occurrence[0]] = tag;
		(*input)[occurrence[1]] = tag;
		in_quotes = '\0';
		ft_memset(occurrence, -1, 8);
		identify_idx_of_occurrences((*input), &in_quotes, occurrence, &idx);
	}
	replace_non_literal_spaces(input);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_sqpa_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:44:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/09 18:52:46 by hbourlot         ###   ########.fr       */
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

static void	replace_non_literal_spaces(char *input)
{
	int		i;
	bool	in_quotes;

	in_quotes = false;
	i = 0;
	while (input[i])
	{
		if (input[i] == REP_DOUBLE_QUOTE || input[i] == REP_SINGLE_QUOTE)
			in_quotes = !in_quotes;
		else if (input[i] == ' ' && !in_quotes)
			input[i] = REP_SPACE;
		i++;
	}
}

static void replace_pa_tokens_in_literal(char *input)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (input && input[i])
	{
		if (input[i] == REP_DOUBLE_QUOTE || input[i] == REP_SINGLE_QUOTE)
			in_quotes = !in_quotes;
		if (in_quotes)
		{
			if (input[i] == '|')
				input[i] = REP_PIPE;
			else if (input[i] == '&')
				input[i] = REP_AND;
		}
		i++;
	}
}
/// @brief Identifies and replaces specific characters in the 
///		input string based on context.
///        - Replaces paired single ('') and double ("") quotes with respective tags.
///        - Converts spaces outside quotes to REP_SPACE.
///        - Converts '|' to REP_PIPE and '&' to REP_AND inside quotes.
/// @param input The string to be processed.
void	identify_and_replace_sqpa_tokens(char *input)
{
	int idx;
	char in_quotes;
	int occurrence[2];
	char tag;

	idx = 0;
	in_quotes = '\0';
	ft_memset(occurrence, -1, 8);
	identify_idx_of_occurrences(input, &in_quotes, occurrence, &idx);
	while (occurrence[0] != -1 && occurrence[1] != -1)
	{
		if (in_quotes == '\'')
			tag = REP_SINGLE_QUOTE;
		else if (in_quotes == '"')
			tag = REP_DOUBLE_QUOTE;

		input[occurrence[0]] = tag;
		input[occurrence[1]] = tag;
		in_quotes = '\0';
		ft_memset(occurrence, -1, 8);
		identify_idx_of_occurrences(input, &in_quotes, occurrence, &idx);
	}
	replace_non_literal_spaces(input);
	replace_pa_tokens_in_literal(input);
}

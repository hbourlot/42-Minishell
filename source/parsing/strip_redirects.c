/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:51:28 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/04 18:14:20 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	toggle_quotes(char *input, bool *in_quotes, int i)
{
	if (input[i] && (input[i] == REP_SQ || input[i] == REP_DQ))
		*in_quotes = !*in_quotes;
}

void	skip_spaces_and_token(char *input, int *i, bool *in_quotes)
{
	int	idx;
	const char	*all_tokens[] = {"||", "|", "&&", ">>", "<<", "<", ">", NULL};
	
	while (input[*i] && input[*i] == REP_SPACE)
	{
		toggle_quotes(input, in_quotes, *i);
		(*i)++;
	}
	while (input[*i] && input[*i] != REP_SPACE)
	{
		toggle_quotes(input, in_quotes, *i);
		if  (!*in_quotes && find_string_match(&input[*i], all_tokens, &idx) == CMP_OK)
			return;
		(*i)++;
	}
}

void	strip_redirects(char *input, const char *tokens[])
{
	int			start;
	int			i;
	int			idx;
	bool		in_quotes;

	i = 0;
	in_quotes = false;
	while (input && input[i])
	{
		toggle_quotes(input, &in_quotes, i);
		if (!in_quotes && input[i] && find_string_match(&input[i], tokens,
				&idx) == OK)
		{
			start = i;
			i += ft_strlen(tokens[idx]);
			skip_spaces_and_token(input, &i, &in_quotes);
			truncate_range(input, start, i - start);
			strip_redirects(input, tokens);
			return ;
		}
		i++;
	}
}

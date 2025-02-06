/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:51:28 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/06 12:58:34 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_redirects(char *input, const char *tokens[])
{
	const char *all_tokens[] = {"||", "|", "&&", ">>", "<<", "<", ">", NULL};
	int	start;
	int	i;
	int	idx;
	int	in_quotes;

	i = 0;
	in_quotes = false;
	while (input && input[i])
	{
		if (input[i] && (input[i] == REP_SINGLE_QUOTE || input[i] == REP_DOUBLE_QUOTE))
			in_quotes = !in_quotes;
		if (!in_quotes && input[i] && find_string_match(&input[i], tokens, &idx) == OK)
		{
			start = i;
			i += ft_strlen(tokens[idx]);
			while (input[i] && input[i] == REP_SPACE)
				i++;
			while (input[i] && input[i] != REP_SPACE && find_string_match(&input[i], all_tokens, &idx) != OK)
				i++;
			truncate_range(input, start, i - start);
			strip_redirects(input,  tokens);
		}
		i++;
	}
}

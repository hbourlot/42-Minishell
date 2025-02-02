/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_quotes_matching.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:29:40 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 14:19:39 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

bool is_quotes_maching(char *input)
{
	int	i;
	bool in_quotes;

	i = 0;
	in_quotes = false;
	while (input[i])
	{
		if (input[i] == REP_DOUBLE_QUOTE || input[i] == REP_SINGLE_QUOTE)
			in_quotes = !in_quotes;
		if (!in_quotes && input[i] == '"' || input[i] == '\'')
		{
			set_error_in(1, "Opened quotes", __func__, false);
			return (false);
		}
		i++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:33:57 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/07 23:18:35 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token get_t_token(char *src, size_t size)
{
	if (ft_strncmp(src, "|", size) == CMP_OK)
		return (PIPE_SINGLE);
	else if (ft_strncmp(src, "||", size) == CMP_OK)
		return (PIPE_DOUBLE);
	else if (ft_strncmp(src, "&&", size) == CMP_OK)
		return (AND_DOUBLE);
	else if (ft_strncmp(src, "<", size) == CMP_OK)
		return REDIRECT_LEFT_SINGLE;
	else if (ft_strncmp(src, "<<", size) == CMP_OK)
		return REDIRECT_LEFT_DOUBLE;
	else if (ft_strncmp(src, ">", size) == CMP_OK)
		return REDIRECT_RIGHT_SINGLE;
	else if (ft_strncmp(src, ">>", size) == CMP_OK)
		return REDIRECT_RIGHT_DOUBLE;
	return (NO_TOKEN);
}

void get_redirect_complement(char *src, int *start, int *end, int redirect_size)
{
	int		i;
	int		idx;
	bool	in_quotes;
	const char *tokens[] = {"||", "|", "&&", ">>", "<<", "<", ">", NULL};

	i = 0;
	in_quotes = false;
	if (!src)
		return ;
	i += redirect_size;
	while (src[i] && src[i] == REP_SPACE)
		i++;
	if (src[i] && (src[i] == REP_SINGLE_QUOTE || src[i] == REP_DOUBLE_QUOTE))
	{
		in_quotes = !in_quotes;
		i++;
	}
	*start = i;
	while (src[i] && src[i] != REP_SPACE && src[i] != REP_SINGLE_QUOTE && src[i] != REP_DOUBLE_QUOTE)
	{
		if (!in_quotes && find_string_match(&src[i], tokens, &idx) == OK)
			break;
		i++;
	}
	*end = i;
}

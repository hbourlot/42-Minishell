/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:39:46 by joralves          #+#    #+#             */
/*   Updated: 2025/01/13 16:55:17 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(char *src)
{
	int		count;
	char	quote;

	count = 0;
	while (src && *src)
	{
		if (*src == REP_SINGLE_QUOTE || *src == REP_DOUBLE_QUOTE)
		{
			count++;
			quote = *src++;
			while (*src && *src != quote)
				src++;
			if (*src == quote)
				src++;
		}
		else if (*src)
		{
			count++;
			while (*src && *src != REP_SINGLE_QUOTE && *src != REP_DOUBLE_QUOTE)
				src++;
		}
	}
	return (count);
}

static char	*extract_quoted_substring(char *str, int *i)
{
	int		start;
	char	quote;
	char	*result;

	start = *i;
	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	result = ft_substr(str, start, *i - start);
	if (!result)
		return (NULL);
	return (result);
}

static char	*extract_unquoted_substring(char *str, int *i)
{
	int		start;
	char	*result;

	start = *i;
	while (str[*i] && str[*i] != REP_SINGLE_QUOTE
		&& str[*i] != REP_DOUBLE_QUOTE)
		(*i)++;
	result = ft_substr(str, start, *i - start);
	if (!result)
		return (NULL);
	return (result);
}

char	**tokenize_element(char *element)
{
	int		i;
	char	**cmd_tokens;
	int		idx;

	idx = 0;
	i = 0;
	cmd_tokens = ft_calloc(count_tokens(element) + 1, sizeof(char *));
	if (!cmd_tokens)
		return (free(element), NULL);
	while (element && element[i])
	{
		if (element[i] == REP_SINGLE_QUOTE || element[i] == REP_DOUBLE_QUOTE)
		{
			cmd_tokens[idx] = extract_quoted_substring(element, &i);
			if (!cmd_tokens[idx++])
				return (free_split(cmd_tokens), NULL);
		}
		else if (element[i])
		{
			cmd_tokens[idx] = extract_unquoted_substring(element, &i);
			if (!cmd_tokens[idx++])
				return (free_split(cmd_tokens), NULL);
		}
	}
	return (cmd_tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:39:46 by joralves          #+#    #+#             */
/*   Updated: 2025/02/21 16:22:51 by joralves         ###   ########.fr       */
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
		if (*src == REP_SQ || *src == REP_DQ)
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
			while (*src && *src != REP_SQ && *src != REP_DQ)
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
	while (str[*i] && str[*i] != REP_SQ && str[*i] != REP_DQ)
		(*i)++;
	result = ft_substr(str, start, *i - start);
	if (!result)
		return (NULL);
	return (result);
}

static char	**tokenize_element(char *element)
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
		if (element[i] == REP_SQ || element[i] == REP_DQ)
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

char	*expand_command_input(char *input, bool *expanded)
{
	char	*expand_input;
	char	**elements;
	if(!*input)
		return(ft_strdup(input));
	elements = tokenize_element(input);
	if (!elements)
		return (NULL);
	expand_input = handle_command_elements(elements, expanded);
	if (!expand_input)
		handle_error(E_MALLOC, NULL, __func__);
	return (expand_input);
}

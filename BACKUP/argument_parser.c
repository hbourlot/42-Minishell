/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:59:48 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/11 17:33:21 by joralves         ###   ########.fr       */
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
		while (*src && *src == ' ')
			src++;
		if (*src == '\'' || *src == '\"')
		{
			count++;
			quote = *src++;
			while (*src && *src != quote)
				src++;
			if (*src == quote)
				src++;
		}
		else if (*src && *src != ' ')
		{
			count++;
			while (*src && *src != ' ' && *src != '\'' && *src != '\"')
				src++;
		}
	}
	return (count);
}

static int	handle_quotes(char *str, char **temp, int *idx, int *i)
{
	int		start;
	char	quote;

	start = *i;
	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	temp[*idx] = ft_substr(str, start, *i - start);
	if (!temp[*idx])
		return (free_split(temp), -1);
	(*idx)++;
	return (0);
}

static int	split_string_with_quotes(char *str, char **temp, int *idx)
{
	int	i;
	int	start;

	i = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (handle_quotes(str, temp, idx, &i) == -1)
				return (-1);
		}
		else if (str[i] && str[i] != ' ')
		{
			start = i;
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
				i++;
			temp[*idx] = ft_substr(str, start, i - start);
			if (!temp[*idx])
				return (free_split(temp), -1);
			(*idx)++;
		}
	}
	return (0);
}

char	**process_command_input(char *input)
{
	int		idx;
	char	**temp;
	int		i;

	i = 0;
	idx = 0;
	temp = ft_calloc(count_tokens(input) + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	if (split_string_with_quotes(input, temp, &idx) != 0)
		return (NULL);
	temp[idx] = NULL;
	while (i < idx)
	{
		temp[i] = process_variables(temp[i]);
		if (temp[i])
			printf("%s\n", temp[i]);
		i++;
	}
	return (temp);
}

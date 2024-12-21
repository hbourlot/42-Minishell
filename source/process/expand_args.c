/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:59:00 by joralves          #+#    #+#             */
/*   Updated: 2024/12/21 02:18:19 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_aux(char *str)
{
	char	*temp;
	char	**splited;
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	splited = ft_split(str, '$');
	while (splited[i])
	{
		temp = getenv(splited[i]);
		res = ft_append_and_free(res, temp);
		free(splited[i]);
		i++;
	}
	free(splited);
	free(str);
	return (res);
}

static char	*expand_var(char *str)
{
	char	**splited;
	char	*temp;
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	if (ft_strchr("\'", str[0]))
		return (ft_substr(str, 1, ft_strlen(str) - 2));
	if (ft_strchr("\"", str[0]))
		str = ft_substr(str, 1, ft_strlen(str) - 2);
	splited = ft_split_keep_charset(str, " \'");
	while (splited[i])
	{
		temp = ft_strchr(splited[i], '$');
		if (temp && (*(temp + 1) != '\0' && *(temp + 1) != ' '))
			splited[i] = expand_aux(splited[i]);
		res = ft_append_and_free(res, splited[i]);
		free(splited[i]);
		i++;
	}
	free(splited);
	free(str);
	return (res);
}

static int	count_words(char *src)
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

static int	args_aux(char *str, char **temp, int *idx)
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

char	**split_args(char *input)
{
	int		idx;
	char	**temp;
	int		i;

	i = 0;
	idx = 0;
	temp = ft_calloc(count_words(input) + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	if (args_aux(input, temp, &idx) != 0)
		return (NULL);
	temp[idx] = NULL;
	while (i < idx)
	{
		temp[i] = expand_var(temp[i]);
		printf("%s\n", temp[i]);
		i++;
	}
	return (temp);
}

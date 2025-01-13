/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_bash_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 01:12:19 by joralves          #+#    #+#             */
/*   Updated: 2025/01/13 15:03:02 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_count(char *src)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (src && src[i])
	{
		count++;
		if (src[i] == '$')
		{
			i++;
			if (src[i] == '\0')
				return (count);
			if (src[i] == '$' || src[i] == '?')
				i++;
			else
				while (src[i] && src[i] != '$')
					i++;
		}
		else
			while (src[i] && src[i] != '$')
				i++;
	}
	return (count);
}

static int	extract_token(char *src, char **dest, int *i, int *idx)
{
	int	start;

	start = *i;
	(*i)++;
	while (src[*i] && src[*i] != '$')
		(*i)++;
	dest[*idx] = ft_substr(src, start, *i - start);
	if (!dest[*idx])
		return (-1);
	(*idx)++;
	return (0);
}

static char	*extract_special_token(char *src, int *i)
{
	char	*result;

	result = ft_substr(src + *i, 0, 2);
	if (!result)
		return (NULL);
	*i += 1;
	return (result);
}

char	**tokenize_bash_variables(char *src)
{
	char	**tokens;
	int		i;
	int		idx;

	i = 0;
	idx = 0;
	tokens = ft_calloc(token_count(src) + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	while (src && src[i])
	{
		if (src[i] == '$' && (src[i + 1] == '$' || src[i + 1] == '?' || src[i
					+ 1] == '\0'))
		{
			tokens[idx] = extract_special_token(src, &i);
			if (!tokens[idx++])
				return (NULL);
			if (src[i++] == '\0')
				break ;
		}
		else if (extract_token(src, tokens, &i, &idx) != 0)
			return (NULL);
	}
	tokens[idx] = NULL;
	return (tokens);
}

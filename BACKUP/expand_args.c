/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:59:00 by joralves          #+#    #+#             */
/*   Updated: 2025/01/16 16:33:36 by hbourlot         ###   ########.fr       */
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

static int	tokenize_bash_variables(char *src, char **dest)
{
	int	i;
	int	idx;

	i = 0;
	idx = 0;
	while (src && src[i])
	{
		if (src[i] == '$')
		{
			if (src[i + 1] == '$' || src[i + 1] == '?' || src[i + 1] == '\0')
			{
				dest[idx] = ft_substr(src + i++, 0, 2);
				if (!dest[idx++])
					return (-1);
				if (src[i++] == '\0')
					break ;
			}
			else if (extract_token(src, dest, &i, &idx) != 0)
				return (-1);
		}
		else if (extract_token(src, dest, &i, &idx) != 0)
			return (-1);
	}
	dest[idx] = NULL;
	return (0);
}

static int	expand_shell_variable(char *var_name, char **expanded_value)
{
	char	*temp;

	if (var_name[1] == '$')
	{
		*expanded_value = ft_itoa(getpid());
		if (!*expanded_value)
			return (-1);
	}
	else if (var_name[1] == '?')
	{
		*expanded_value = ft_itoa(get_shell()->exit_status);
		if (!*expanded_value)
			return (-1);
	}
	else
	{
		temp = getenv(var_name + 1);
		*expanded_value = ft_strdup(temp);
		if (!*expanded_value)
			return (-1);
	}
	return (0);
}

static char	*expand_variables(char *str)
{
	char	**tokens;
	int		i;
	char	*result;
	char	*expanded_value;

	expanded_value = NULL;
	result = NULL;
	i = 0;
	tokens = ft_calloc(token_count(str) + 1, sizeof(char *));
	if (!tokens || tokenize_bash_variables(str, tokens) != 0)
		return (NULL);
	while (tokens[i])
	{
		if (tokens[i][0] == '$')
		{
			if (tokens[i][1] != '\0')
			{
				if (expand_shell_variable(tokens[i], &expanded_value) != 0)
					return (free_split(tokens), free(str), NULL);
				free(tokens[i]);
				tokens[i] = expanded_value;
			}
		}
		result = ft_append_and_free(result, tokens[i]);
		if (!result)
			return (free_split(tokens), free(str), NULL);
		i++;
	}
	return (free_split(tokens), free(str), result);
}

char	*process_variables(char *str)
{
	char	**tokens;
	int		i;
	char	*result;

	print_execve_parameters(str);
	printf("HERe\n");
	result = NULL;
	i = 0;
	if (ft_strchr("\'", str[0]))
	{
		result = ft_substr(str, 1, ft_strlen(str) - 2);
		if (!result)
			return (free(str), NULL);
		return (free(str), result);
	}
	if (ft_strchr("\"", str[0]))
		str = ft_substr(str, 1, ft_strlen(str) - 2);
	tokens = ft_split_keep_charset(str, " \'");
	while (tokens[i])
	{
		printf("Tokens[%d] process_variables %s\n", i, tokens[i]);
		if (ft_strchr(tokens[i], '$'))
			tokens[i] = expand_variables(tokens[i]);
		result = ft_append_and_free(result, tokens[i]);
		free(tokens[i]);
		i++;
	}
	return (free(tokens), free(str), result);
}

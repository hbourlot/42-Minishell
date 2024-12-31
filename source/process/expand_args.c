/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:59:00 by joralves          #+#    #+#             */
/*   Updated: 2024/12/27 01:52:10 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_string(char *str, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		while (str[i] && str[i] != sep)
			i++;
		if (str[i] && str[i] == sep)
			count++;
		while (str[i] && str[i] == sep)
			i++;
	}
	return (count);
}

static char	**create_splited(char *str, char sep)
{
	char	**temp;
	int		start;
	int		i;
	int		idx;

	idx = 0;
	start = 0;
	i = 0;
	temp = ft_calloc(count_string(str, '$'), sizeof(char *));
	while (str && str[i])
	{
		while (str[i] && str[i] != sep)
			i++;
		if (str[i] && str[i] == sep)
		{
			temp[idx] = ft_substr(str, start, i - start);
			start = i;
			idx++;
		}
		while (str[i] && str[i] == sep)
			i++;
	}
	temp[idx] = NULL;
	return (temp);
}

static char	*expand_aux(char *str)
{
	char	**splited;
	int		i;
	char	*res;
	char	*temp;

	res = NULL;
	i = 0;
	// splited = ft_split(str, '$');
	printf("Count_str %d\n", count_string(str, '$'));
	splited = create_splited(str, '$');
	if (!splited)
		return (NULL);
	while (splited[i])
	{
		printf("splited %s\n", splited[i]);
		temp = getenv(splited[i]);
		res = ft_append_and_free(res, temp);
		free(splited[i]);
		i++;
	}
	free(splited);
	free(str);
	return (res);
}

char	*expand_var(char *str)
{
	char	**splited;
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
		if (ft_strchr(splited[i], '$'))
			splited[i] = expand_aux(splited[i]);
		res = ft_append_and_free(res, splited[i]);
		free(splited[i]);
		i++;
	}
	free(splited);
	free(str);
	return (res);
}

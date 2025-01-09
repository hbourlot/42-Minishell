/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_charset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:45:38 by joralves          #+#    #+#             */
/*   Updated: 2025/01/08 15:55:37 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset && charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_str(char *str, char *charset)
{
	int	count;
	int	i;
	int	in_charset;

	count = 0;
	i = 0;
	while (str[i])
	{
		in_charset = is_charset(str[i], charset);
		if (!in_charset)
		{
			count++;
			while (str[i] && !is_charset(str[i], charset))
				i++;
		}
		else
		{
			count++;
			while (str[i] && is_charset(str[i], charset))
				i++;
		}
	}
	return (count);
}

static char	**string_allocation(char **array, char *str, char *charset,
		int *idx)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (str && str[i])
	{
		if (is_charset(str[i], charset) == 0)
		{
			start = i;
			while (str[i] && is_charset(str[i], charset) == 0)
				i++;
		}
		else if (is_charset(str[i], charset) == 1)
		{
			start = i;
			while (str[i] && is_charset(str[i], charset) == 1)
				i++;
		}
		array[*idx] = ft_substr(str, start, i - start);
		if (!array[*idx])
			return (free_split(array), NULL);
		*idx = *idx + 1;
	}
	return (array);
}

char	**ft_split_keep_charset(char *str, char *charset)
{
	char	**array;
	int		idx;

	idx = 0;
	array = malloc((count_str(str, charset) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (string_allocation(array, str, charset, &idx) == NULL)
		return (NULL);
	array[idx] = NULL;
	return (array);
}

// int	main(void)
// {
// 	int i = 0;

// 	char str[] = "'$USER' '$home' '$path'";
// 	// printf("%d", count_str(str, '\''));
// 	char **array = ft_split_keep_charset(str, "\'$");
// 	while (array[i])
// 	{
// 		printf("%s\n", array[i]);
// 		i++;
// 	}
// 	free_split(array);
// }
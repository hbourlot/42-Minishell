/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_sep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:54:31 by joralves          #+#    #+#             */
/*   Updated: 2024/12/12 15:53:58 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_str(char *str, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != sep)
			count++;
		while (str[i] != sep)
			i++;
		if (str[i] == sep)
			count++;
		while (str[i] == sep)
			i++;
	}
	return (count);
}

static char	**string_allocation(char **array, char *str, char sep, int *idx)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != sep)
		{
			start = i;
			while (str[i] != sep)
				i++;
		}
		else if (str[i] == sep)
		{
			start = i;
			while (str[i] == sep)
				i++;
		}
		array[*idx] = ft_substr(str, start, i - start);
		if (!array[*idx])
			return (free_split(array), NULL);
		*idx = *idx + 1;
	}
	return (array);
}

char	**ft_split_keep_sep(char *str, char sep)
{
	char	**array;
	int		idx;

	idx = 0;
	array = malloc((count_str(str, sep) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (string_allocation(array, str, sep, &idx) == NULL)
		return (NULL);
	array[idx] = NULL;
	return (array);
}

// int	main(void)
// {
// 	int i = 0;

// 	char str[] = "'%USER' '%home'' '%path'";
// 	// printf("%d", count_str(str, '\''));
// 	char **array = ft_split_keep_sep(str, '\'');
// 	while (array[i])
// 	{
// 		printf("%s\n", array[i]);
// 		i++;
// 	}
// 	free_split(array);
// }
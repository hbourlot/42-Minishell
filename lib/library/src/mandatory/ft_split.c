/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:30:43 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/10 23:31:22 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Allocates memory for array[idx] based on buffer size.
/// @param array The array of strings.
/// @param buffer The size of memory to allocate.
/// @param idx The index in the array where memory is allocated.
/// @return Returns 1 if memory allocation fails, otherwise 0.
static int	allocate_memory(char **array, size_t buffer, size_t idx)
{
	size_t	i;

	i = 0;
	array[idx] = ft_calloc(buffer, sizeof(char));
	if (!array[idx])
	{
		while (i < idx)
		{
			free(array[i]);
			i++;
		}
		free(array);
		return (1);
	}
	return (0);
}

/// @brief Splits string s into array based on delimiter c.
/// @param array The array where split strings are stored.
/// @param s The string to split.
/// @param c The delimiter character.
/// @return Returns 1 if memory allocation fails, otherwise 0.
static int	split_to_array(char **array, char const *s, const char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			++s;
		while (*s != c && *s)
		{
			++s;
			len++;
		}
		if (len)
		{
			if (allocate_memory(array, len + 1, i))
				return (1);
			ft_strlcpy(array[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

/// @brief Counts the number of words in string s based on delimiter c.
/// @param s The string to count words in.
/// @param c The delimiter character.
/// @return Returns the number of words found in the string.
static int	count_words_in_string(char const *s, char c)
{
	size_t	i;
	size_t	new_word;

	new_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && i == 0)
			new_word++;
		if (s[i + 1] != c && s[i] == c && s[i + 1])
			new_word++;
		i++;
	}
	return (new_word);
}

/// @brief Splits string s into an array of strings based on delimiter c.
/// @param s The string to split.
/// @param c The delimiter character.
/// @return Returns a dynamically allocated array of strings split from s.
char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (NULL == s)
		return (NULL);
	words = count_words_in_string(s, c);
	array = ft_calloc((words + 1), sizeof(char *));
	if (!array)
		return (NULL);
	array[words] = NULL;
	if (split_to_array(array, s, c))
		return (NULL);
	return (array);
}

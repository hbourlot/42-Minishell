/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:59:48 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/30 11:24:25 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Allocates memory for array[idx] based on buffer size.
/// @param array The array of strings.
/// @param buffer The size of memory to allocate.
/// @param idx The index in the array where memory is allocated.
/// @return Returns 1 if memory allocation fails, otherwise 0.
static int	do_malloc(char **array, size_t buffer, size_t idx)
{
	size_t	i;

	i = 0;
	array[idx] = (char *)malloc(sizeof(char) * buffer);
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

/// @brief Counts the number of words in the string based on spaces or quotes.
/// @param s The input string.
/// @param words Pointer to integer that will hold how many words it has
static void	count_words(const char *s, int *words)
{
	int	in_quote;
	int	in_word;

	in_quote = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == '\'')
			in_quote = !in_quote;
		if (*(s + 1) && *s == '\'' && *(s + 1) == '\'')
			*words += 1;
		else if (*s != ' ' || in_quote)
		{
			if (!in_word)
			{
				*words += 1;
				in_word = 1;
			}
		}
		else if (*s == ' ' && !in_quote)
			in_word = 0;
		s++;
	}
}

static int	process_word(char **array, char *start, char *end, int i)
{
	size_t	len;

	len = 0;
	if (do_malloc(array, (end - start) + 1, i))
		return (1);
	while (start < end)
	{
		if (*start != '\'')
			array[i][len++] = *start;
		start++;
	}
	array[i][len] = '\0';
	return (0);
}

/// @brief Duplicates and allocates memory for words inside array.
/// @param array The array to store split words.
/// @param s The input string.
/// @return Returns 1 if memory allocation fails, otherwise 0.
static int	duplicate(char **array, const char *s)
{
	int		in_quotes;
	int		i;
	char	*start;

	i = 0;
	in_quotes = 0;
	while (*s)
	{
		while (*s == ' ')
			s++;
		start = (char *)s;
		while (*s && (*s != ' ' || in_quotes))
		{
			if (*s == '\'')
				in_quotes = !in_quotes;
			s++;
		}
		if (s > start)
		{
			if (process_word(array, start, (char *)s, i))
				return (1);
			i++;
		}
	}
	return (0);
}

/// @brief Splits the string s into an array of words based
///	on spaces and quotes.
/// @param s The string to split.
/// @return Returns a dynamically allocated array of words split from s.
char	**get_command_args(char *argv)
{
	char	**array;
	char	reference;
	int		words;

	words = 0;
	if (NULL == argv)
		return (NULL);
	count_words(argv, &words);
	if (words == 0)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array[words] = NULL;
	if (duplicate(array, argv))
		return (free_split(array), NULL);
	return (array);
}

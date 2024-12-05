/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:26:52 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/05 20:31:02 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef CMP_OK
# define CMP_OK 0
#endif

/// @brief Sorts tokens in descending order of length.
/// @param tokens The array of tokens to sort.
static void	sort_tokens_by_length(const char *tokens[])
{
	int			i;
	int			j;
	const char	*temp;

	i = 0;
	while (tokens[i])
	{
		j = i + 1;
		while (tokens[j])
		{
			if (ft_strlen(tokens[j]) > ft_strlen(tokens[i]))
			{
				temp = tokens[i];
				tokens[i] = tokens[j];
				tokens[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/// @brief Counts the number of parts in the string split by tokens.
/// @param src The input string.
/// @param tokens The array of tokens to split by.
/// @return The number of parts found.
static int	count_parts(char *src, const char *tokens[])
{
	int	i;
	int	j;
	int	count;
	int	len;

	count = 1;
	i = 0;
	while (src[i])
	{
		j = -1;
		while (tokens[++j])
		{
			len = ft_strlen(tokens[j]);
			if (ft_strncmp(&src[i], tokens[j], len) == CMP_OK)
			{
				count++;
				i += len - 1;
				break ;
			}
		}
		i++;
	}
	return (count);
}

/// @brief Extracts the next part of the string split by tokens.
/// @param src Pointer to the input string (will be updated).
/// @param tokens The array of tokens to split by.
/// @return The next extracted part of the string.
static char	*extract_part(char **src, const char *tokens[])
{
	char	*result;
	int		j;
	int		i;

	i = -1;
	while ((*src)[++i])
	{
		j = -1;
		while (tokens[++j])
		{
			if (ft_strncmp(&(*src)[i], tokens[j],
				ft_strlen(tokens[j])) == CMP_OK)
			{
				result = ft_substr(*src, 0, i);
				if (!result)
					return (NULL);
				*src += i + ft_strlen(tokens[j]);
				return (result);
			}
		}
	}
	result = ft_substr(*src, 0, i);
	if (!result)
		return (NULL);
	return (result);
}

/// @brief Splits a string by multiple tokens into an array of strings.
/// @param src The input string.
/// @param tokens The array of tokens to split by.
/// @return A NULL-terminated array of strings resulting from the split.
char	**split_by_multiple_tokens(char *src, const char *tokens[])
{
	char	**split;
	int		parts;
	int		idx;

	if (!src || !tokens)
		return (NULL);
	sort_tokens_by_length(tokens);
	parts = count_parts(src, tokens);
	split = malloc((parts + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	idx = 0;
	while (idx < parts)
	{
		split[idx] = extract_part(&src, tokens);
		if (!split[idx])
			return (free_split(split), NULL);
		idx++;
	}
	split[idx] = NULL;
	return (split);
}

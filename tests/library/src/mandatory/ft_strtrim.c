/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:02:59 by hbourlot          #+#    #+#             */
/*   Updated: 2024/07/08 14:33:00 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Checks if a character 'c' is present in the string 'set'.
/// @param c The character to search for.
/// @param set The string in which to search for the character.
/// @return 1 if 'c' is found in 'set', 0 otherwise.
static int	is_in(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/// @brief Allocates and returns a copy of 's1' with the leading and trailing
/// characters in 'set' removed.
/// @param s1 The string to trim.
/// @param set The set of characters to trim.
/// @return A newly allocated trimmed string, or NULL if allocation fails.
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*temp;

	len = ft_strlen(s1);
	start = 0;
	end = len - 1;
	while (is_in(s1[start], set) == 1)
		start++;
	while (is_in(s1[end], set) == 1 && end != 0)
		end--;
	if (end == 0)
		return (ft_strdup(""));
	temp = (char *)malloc(sizeof(char) * ((end - start) + 2));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &s1[start], (end - start + 2));
	return (temp);
}

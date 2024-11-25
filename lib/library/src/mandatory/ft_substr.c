/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:01:05 by hbourlot          #+#    #+#             */
/*   Updated: 2024/07/08 14:32:55 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function allocates (using 'malloc()') and returns a substring from the
** string 's'.
** The substring begins at index 'start' and is as maximum size 'len'.
*/

#include "libft.h"

/// @brief Extracts a substring from a given string.
/// @param s The original string.
/// @param start The starting index of the substring.
/// @param len The length of the substring.
/// @return A newly allocated string containing the substring,
///	or NULL if allocation fails.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	while (i < len && start <= ft_strlen(s))
	{
		temp[i] = s[start];
		i++;
		start++;
	}
	temp[i] = '\0';
	return (temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:54:36 by hbourlot          #+#    #+#             */
/*   Updated: 2024/08/14 14:32:20 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Copies the string src to dest including the null terminator.
/// @param dest The destination string where the copy will be stored.
/// @param src The source string to be copied.
/// @return Returns a pointer to the destination string dest.
// static char	*ft_strcpy(char *dest, const char *src)
// {
// 	size_t	i;

// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

/// @brief Duplicates the string s.
/// @param s The string to be duplicated.
/// @return Returns a pointer to a newly allocated string which
///			is a duplicate of s, or NULL if allocation fails.
char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	ft_strcpy(dup, s);
	return (dup);
}

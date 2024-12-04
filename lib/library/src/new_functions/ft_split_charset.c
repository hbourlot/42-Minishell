/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:57:58 by joralves          #+#    #+#             */
/*   Updated: 2024/12/04 15:55:36 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(const char *s, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_charset(s[i], charset) == 0)
			count++;
		while (is_charset(s[i], charset) == 0 && s[i] != '\0')
			i++;
		while (is_charset(s[i], charset) == 1 && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**each_alloc(char **dest, int idx, int len)
{
	dest[idx] = ft_calloc((len + 1), sizeof(char));
	if (!(dest[idx]))
	{
		while (idx >= 0)
		{
			free(dest[idx]);
			idx--;
		}
		free(dest);
		return (NULL);
	}
	return (dest);
}

static char	*ft_strncpy(char *dest, const char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**dest_allocation(char **dest, char const *s, char *charset)
{
	int	i;
	int	i_dst;
	int	start;

	i = 0;
	i_dst = 0;
	while (s[i])
	{
		if (is_charset(s[i], charset) == 0)
		{
			start = i;
			while (is_charset(s[i], charset) == 0 && s[i])
				i++;
			if (i > 0 && is_charset(s[i - 1], charset) == 0)
			{
				if (!each_alloc(dest, i_dst, (i - start)))
					return (NULL);
				ft_strncpy(dest[i_dst++], &s[start], (i - start));
			}
		}
		else
			i++;
	}
	dest[i_dst] = NULL;
	return (dest);
}

char	**ft_split_charset(char const *s, char *charset)
{
	char	**dest;
	int		count;

	count = count_words(s, charset);
	dest = ft_calloc((count + 1), sizeof(char *));
	if (!(dest))
		return (NULL);
	dest_allocation(dest, s, charset);
	return (dest);
}

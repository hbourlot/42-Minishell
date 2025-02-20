/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:59:42 by joralves          #+#    #+#             */
/*   Updated: 2025/02/20 18:15:52 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_wildcard(const char *pattern, const char *filename)
{
	int	i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			while (filename[i])
			{
				if (match_wildcard(pattern + 1, filename + i))
					return (1);
				i++;
			}
			return (0);
		}
		if (pattern[i] != filename[i])
			return (0);
		i++;
	}
	return (pattern[i] == '\0' && filename[i] == '\0');
}

void	expand_wildcard(char *pattern)
{
	struct dirent	*entry;
	DIR				*directory;

	directory = opendir(".");
	while ((entry = readdir(directory)) != NULL)
	{
		if (match_wildcard(pattern, entry->d_name))
			printf("%s\n", entry->d_name);
	}
	closedir(directory);
}

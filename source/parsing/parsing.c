/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:52 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/01 18:42:41 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

bool	is_delimiters_together(char *input, const char **delimiters)
{
	int		index1;
	int		index2;
	int		len1;
	int		len2;

	index1 = 0;
	while (delimiters[index1])
	{
		len1 = ft_strlen(delimiters[index1]);
		if (!ft_strncmp(input, delimiters[index1], len1))
		{
			index2 = 0;
			while (delimiters[index2])
			{
				len2 = ft_strlen(delimiters[index2]);
				if (!ft_strncmp(input + len1, delimiters[index2], len2))
					return (true);		
			}
			index2++;
		}
		index1++;
	}
	return (false);
}

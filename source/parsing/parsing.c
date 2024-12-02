/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:52 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/02 09:28:24 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

bool	is_delimiters_together(char *input, const char **delimiters)
{
	int	i;
	int	j;
	int	k;
	
	i = -1;
	while (delimiters[++i])
	{
		j = -1;
		while (input[++j])
		{
			if (!ft_strncmp(input + j, delimiters[i], ft_strlen(delimiters[i])))
			{
				k = -1;
				while (delimiters[++k])
				{
					if (k == i)
						continue;
					if (!ft_strncmp(input + j + ft_strlen(delimiters[i]), delimiters[k], ft_strlen(delimiters[k])))
						return (true);
				}
			}	
		}
	}
	return (false);
}
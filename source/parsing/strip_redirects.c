/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:51:28 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/23 00:21:43 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strip_redirects(char *input, const char *redirects[])
{
	int start;
	int i;
	int idx;

	i = 0;
	while (input && input[i])
	{
		if (find_string_match(&input[i], redirects, &idx) == OK)
		{
			start = i;
			i += ft_strlen(redirects[idx]);
			while (input[i] && input[i] == ' ')
				i++;
			while (input[i] && input[i] != ' ')
				i++;
			truncate_range(input, start, i - start);
		}
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:33:57 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/23 22:09:01 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token get_t_token(char *src, size_t size)
{
	if (ft_strncmp(src, "|", size) == CMP_OK)
		return (PIPE_SINGLE);
	else if (ft_strncmp(src, "||", size) == CMP_OK)
		return (PIPE_DOUBLE);
	else if (ft_strncmp(src, "&&", size) == CMP_OK)
		return (AND_DOUBLE);
	else if (ft_strncmp(src, "<", size) == CMP_OK)
		return REDIRECT_LEFT_SINGLE;
	else if (ft_strncmp(src, "<<", size) == CMP_OK)
		return REDIRECT_LEFT_DOUBLE;
	else if (ft_strncmp(src, ">", size) == CMP_OK)
		return REDIRECT_RIGHT_SINGLE;
	else if (ft_strncmp(src, ">>", size) == CMP_OK)
		return REDIRECT_RIGHT_DOUBLE;
	return (0);
}

void get_redirect_complement(char *src, int *start, int *end)
{
	int		i;

	i = 0;
	while (src[i] && src[i] == REP_SPACE)
		i++;
	if (src[i] && (src[i] == REP_SINGLE_QUOTE || src[i] == REP_DOUBLE_QUOTE))
		i++;
	*start = i;
	while (src[i] && src[i] != REP_SPACE && src[i] != REP_SINGLE_QUOTE && src[i] != REP_DOUBLE_QUOTE)
		i++;
	*end = i;
}

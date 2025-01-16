/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:33:57 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/16 11:50:13 by hbourlot         ###   ########.fr       */
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

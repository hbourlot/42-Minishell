/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:17:42 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/09 15:49:16 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_spaces(char **src)
{
	if (!src || !*src)
		return;
	while (**src && **src == ' ')
		(*src)++;
}

void skip_character(char **src, char c)
{
	if (!src || !*src)
		return;
	while (**src && **src == c)
		(*src)++;
}

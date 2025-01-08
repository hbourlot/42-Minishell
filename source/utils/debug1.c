/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:36:23 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/07 14:44:51 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_input_splitted(t_shell *data)
{
	int		i;
	char	**tmp_split;

	i = 1;
	tmp_split = data->input_splitted;
	while (*tmp_split)
	{
		printf("Data->input_splitted [%d]: %s\n", i++, *tmp_split);
		tmp_split++;
	}
}

void	debug_readline_processed(t_shell *data)
{
	t_readline	*temp;

	temp = data->readline_processed;
	while (temp)
	{
		if (temp->literal)
			printf("readline_processed->literal:%s:\n", temp->literal);
		if (temp->non_literal)
			printf("readline_processed->non_literal:%s:\n", temp->non_literal);
		temp = temp->next;
	}
}

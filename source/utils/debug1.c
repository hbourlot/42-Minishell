/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:36:23 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/07 15:06:34 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_input_splitted(t_shell *data)
{
	int		i;
	char	**tmp_split;

	i = 1;
	tmp_split = data->rl_splitted;
	while (*tmp_split)
	{
		printf("Data->rl_splitted [%d]: %s\n", i++, *tmp_split);
		tmp_split++;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 21:36:23 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 16:07:30 by joralves         ###   ########.fr       */
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

void	print_execve_parameters(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == REP_DOUBLE_QUOTE)
			printf("(%d - %c)", input[i], input[i]);
		if (input[i] == REP_SINGLE_QUOTE)
			printf("(%d - %c)", input[i], input[i]);
		if (input[i] == REP_SPACE)
			printf("(%d - %c)", input[i], input[i]);
		else
			printf("%c", input[i]);
		i++;
	}
	printf("\n");
}

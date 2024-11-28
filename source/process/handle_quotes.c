/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:27:32 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/28 19:41:04 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	process_pre_command(char *pre_command, t_tokens *tokens)
{
	int	in_single_quotes;
	int	int_double_quotes;
	int	i;

	i = 0;
	in_single_quotes = 0;
	int_double_quotes = 0;
	while (pre_command[i])
	{
		if (pre_command[i] == '\'' && !in_single_quotes)
		{
			in_single_quotes = 1;
		}
	}
}

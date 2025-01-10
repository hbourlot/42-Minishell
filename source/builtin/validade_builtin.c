/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validade_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:56:36 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/10 12:20:11 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_echo(char *input)
{
	int	i;

	i = 0;
	skip_spaces(&input);
	skip_character_diff(&input, ' ');
	while (input[i])
	
}


// void	validate_builtin(t_shell *data, t_cmd *cmd)
// {
// 	is_echo(cmd->input)
}



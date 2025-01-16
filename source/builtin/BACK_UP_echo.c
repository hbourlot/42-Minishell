/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:50:51 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/15 10:56:46 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_block(char *input, int *i)
{
	if (input[*i] == '-')
		(*i)++;
	while (input[*i] && input[*i] == 'n')
		(*i)++;
	return (input[*i] == '\0' || input[*i] == REP_SPACE);
}

static void	skip_spaces_with_idx(char *input, int *i)
{
	while (input[*i] == REP_SPACE)
		(*i)++;
}

static bool	process_flag_blocks(char *input, int *i)
{
	int		start;
	bool	cd;

	cd = false;
	while (input[*i] == '-')
	{
		start = *i;
		if (is_valid_block(input, i))
		{
			truncate_range(&input, start, *i - start);
			cd = true;
			*i = start;
		}
		else
			return (cd);
		skip_spaces_with_idx(input, i);
	}
	return (cd);
}

bool	builtin_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	skip_spaces_with_idx(cmd->input, &i);
	if (ft_strncmp(&cmd->input[i], "echo", 4) != 0)
		return false;
	i += 4;
	skip_spaces_with_idx(cmd->input, &i);
	if (process_flag_blocks(cmd->input, &i) == true)
		cmd->settings.builtin_echo = true;
	return cmd->settings.builtin_echo;
}


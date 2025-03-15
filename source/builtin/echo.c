/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:27:48 by joralves          #+#    #+#             */
/*   Updated: 2025/03/04 20:47:52 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_flag(char **command_arg, bool *remove_nl, int *idx)
{
	int	j;
	int	i;

	i = *idx;
	while (command_arg[i])
	{
		j = 0;
		if (command_arg[i][j++] != '-')
			break ;
		while (command_arg[i][j] == 'n')
			j++;
		if (command_arg[i][j] == '\0')
			*remove_nl = true;
		else if (command_arg[i][j] != '\0')
			break ;
		i++;
	}
	*idx = i;
	return (*remove_nl);
}

/// @brief Handles `echo` to print arguments.
/// @param data The shell structure.
/// @param command_args The arguments array.
/// @details Prints arguments, handling `-n` to suppress newline.
///          Spaces are preserved. Flags validated via `is_valid_flag`.
void	builtin_echo(t_shell *data, char **command_args)
{
	int		idx;
	bool	remove_nl;

	idx = 1;
	remove_nl = false;
	while (command_args[idx])
	{
		if (!remove_nl && idx == 1 && is_valid_flag(command_args, &remove_nl,
				&idx))
			continue ;
		write(1, command_args[idx], ft_strlen(command_args[idx]));
		write(1, " ", (command_args[idx + 1] != NULL));
		idx++;
	}
	if (remove_nl == false)
		printf("\n");
	data->exit_status = 0;
}

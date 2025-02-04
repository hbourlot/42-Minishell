/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:27:48 by joralves          #+#    #+#             */
/*   Updated: 2025/02/02 22:50:04 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_valid_flag(char *command_arg, bool *remove_nl, bool *printable)
{
	int	j;

	j = 1;
	while (command_arg[j] == 'n')
		j++;
	if (command_arg[j] == '\0')
	{
		*remove_nl = true;
		*printable = false;
	}
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
	bool	printable;

	idx = 1;
	remove_nl = false;
	while (command_args[idx])
	{
		printable = true;
		if (command_args[idx][0] == '-')
			is_valid_flag(command_args[idx], &remove_nl, &printable);
		if (printable)
		{
			if (!command_args[idx + 1])
				printf("%s", command_args[idx]);
			else
				printf("%s ", command_args[idx]);
		}
		idx++;
	}
	if (remove_nl == false)
		printf("\n");
	data->exit_status = 0;
}

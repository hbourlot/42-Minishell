/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:41:34 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/08 15:57:48 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Sets the built-in command flag.
/// @param command The last executed command.
/// @details Checks if the command is built-in and updates its settings.
///          No flags are set if empty or only spaces. Uses `ft_strcmp`.
void	set_builtin_flag(t_cmd *command)
{
	int			i;
	char		*args;
	const char	*builtin_functions[] = {"cd", "export", "echo", "env", "unset",
			"exit", "pwd", NULL};

	i = 0;
	if (!command->args || !command->args[0] || all_same_char(command->args[0],
			' '))
		return ;
	args = command->args[0];
	while (builtin_functions[i])
	{
		if (ft_strcmp(args, builtin_functions[i]) == 0)
		{
			command->settings.builtin_id = i + 1;
			command->settings.is_builtin = true;
			break ;
		}
		i++;
	}
	if (command->settings.is_builtin == false)
		command->settings.builtin_id = -1;
}

/// @brief Executes a built-in command.
/// @param data The shell structure.
/// @param command The last executed command.
/// @details Calls the function for the set built-in.
///          Returns ERROR on failure. Handles:
///          `cd`, `pwd`, `echo`, `unset`, `env`, `exit`.
int	process_builtin(t_shell *data, t_cmd *command)
{
	if (command->settings.builtin_id == CD)
	{
		if (builtin_cd(data, command->args) == -1)
			return (ERROR);
	}
	else if (command->settings.builtin_id == PWD)
		builtin_pwd(data);
	else if (command->settings.builtin_id == ECHO)
		builtin_echo(data, command->args);
	else if (command->settings.builtin_id == UNSET)
	{
		if (builtin_unset(data, command->args) == ERROR)
			return (ERROR);
	}
	else if (command->settings.builtin_id == ENV)
		builtin_env(data, command->args);
	else if (command->settings.builtin_id == EXPORT)
	{
		if (builtin_export(data, command->args) == ERROR)
			return (ERROR);
	}
	else if (command->settings.builtin_id == EXIT)
		builtin_exit(data, command);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:41:34 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 23:43:03 by joralves         ###   ########.fr       */
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
	bool		**builtin_flags;
	const char	*builtin_functions[] = {"cd", "export", "echo", "env", "unset",
			"exit", "pwd", NULL};

	builtin_flags = (bool *[]){&command->settings.builtin_cd,
		&command->settings.builtin_export, &command->settings.builtin_echo,
		&command->settings.builtin_env, &command->settings.builtin_unset,
		&command->settings.builtin_exit, &command->settings.builtin_pwd};
	i = 0;
	args = command->args[0];
	if (!args || !*args || all_same_char(args, ' '))
		return ;
	while (builtin_functions[i])
	{
		if (ft_strcmp(args, builtin_functions[i]) == 0)
		{
			*builtin_flags[i] = true;
			command->settings.is_builtin = true;
			break ;
		}
		i++;
	}
}

/// @brief Executes a built-in command.
/// @param data The shell structure.
/// @param command The last executed command.
/// @details Calls the function for the set built-in.
///          Returns ERROR on failure. Handles:
///          `cd`, `pwd`, `echo`, `unset`, `env`, `exit`.
int	process_builtin(t_shell *data, t_cmd *command)
{
	if (command->settings.builtin_cd)
	{
		if (builtin_cd(data, command->args) == -1)
			return (ERROR);
	}
	else if (command->settings.builtin_pwd)
		builtin_pwd(data);
	else if (command->settings.builtin_echo)
		builtin_echo(data, command->args);
	else if (command->settings.builtin_unset)
	{
		if (builtin_unset(data, command->args) == ERROR)
			return (ERROR);
	}
	else if (command->settings.builtin_env)
		builtin_env(data, command->args);
	else if (command->settings.builtin_export)
	{
		if (builtin_export(data, command->args) == ERROR)
			return (ERROR);
	}
	else if (command->settings.builtin_exit)
		builtin_exit(data, command);
	return (0);
}

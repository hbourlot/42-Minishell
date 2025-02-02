/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:41:34 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/01 20:14:37 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Sets the appropriate flag for a built-in command in the command structure.
/// @param command The command structure representing the last executed command.
/// @details Checks if the command is a built-in function and sets the corresponding
///          flag in `command->settings`. If the command is empty or consists only of spaces, 
///          no flags are set. Uses `ft_strcmp` to compare commands against a predefined list.
void	set_builtin_flag(t_cmd *command)
{
	char		*args;
	int			i;
	const char	*builtin_functions[] = {"cd", "export", "echo", "env", "unset",
			"exit", "pwd", NULL};
	bool		*builtin_flags[] = {&command->settings.builtin_cd,
				&command->settings.builtin_export,
				&command->settings.builtin_echo,
				&command->settings.builtin_env,
				&command->settings.builtin_unset,
				&command->settings.builtin_exit,
				&command->settings.builtin_pwd};

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

/// @brief Processes the execution of a built-in command based on the flags in the command structure.
/// @param data The shell structure containing environment mappings and state.
/// @param command The command structure representing the last executed command.
/// @details Checks which built-in command is set in `command->settings` and calls the corresponding
///          function. Returns ERROR if a command fails. This is a temporary function used for testing
///          the execution of built-in commands like `cd`, `pwd`, `echo`, `unset`, `env`, and `exit`.
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

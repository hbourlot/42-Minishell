/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:41:34 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/29 15:31:32 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Sets the appropriate flag for a built-in command in the command structure.
/// @param last_node The command structure representing the last executed command.
/// @details Checks if the command is a built-in function and sets the corresponding
///          flag in `last_node->settings`. If the command is empty or consists only of spaces, 
///          no flags are set. Uses `ft_strcmp` to compare commands against a predefined list.
void	set_builtin_flag(t_cmd *last_node)
{
	char		*command;
	int			i;
	const char	*builtin_functions[] = {"cd", "export", "echo", "env", "unset",
			"exit", "pwd", NULL};
	bool		*builtin_flags[] = {&last_node->settings.builtin_cd,
				&last_node->settings.builtin_export,
				&last_node->settings.builtin_echo,
				&last_node->settings.builtin_env,
				&last_node->settings.builtin_unset,
				&last_node->settings.builtin_exit,
				&last_node->settings.builtin_pwd};

	i = 0;
	command = last_node->args[0];
	if (!command || !*command || all_same_char(command, ' '))
		return ;
	while (builtin_functions[i])
	{
		if (ft_strcmp(command, builtin_functions[i]) == 0)
		{
			*builtin_flags[i] = true;
			break ;
		}
		i++;
	}
}

/// @brief Processes the execution of a built-in command based on the flags in the command structure.
/// @param data The shell structure containing environment mappings and state.
/// @param last_node The command structure representing the last executed command.
/// @details Checks which built-in command is set in `last_node->settings` and calls the corresponding
///          function. Returns ERROR if a command fails. This is a temporary function used for testing
///          the execution of built-in commands like `cd`, `pwd`, `echo`, `unset`, `env`, and `exit`.
int	process_builtin(t_shell *data, t_cmd *last_node)
{
	if (last_node->settings.builtin_cd)
	{
		if (builtin_cd(data, last_node->args) == -1)
			return (ERROR);
	}
	else if (last_node->settings.builtin_pwd)
		builtin_pwd(data);
	else if (last_node->settings.builtin_echo)
		builtin_echo(data, last_node->args);
	else if (last_node->settings.builtin_unset)
	{
		if (builtin_unset(data, last_node->args) == ERROR)
			return (ERROR);
	}
	else if (last_node->settings.builtin_env)
		builtin_env(data, last_node->args);
	else if (last_node->settings.builtin_export)
	{
		builtin_export(data, last_node->args);
	}
	else if (last_node->settings.builtin_exit)
		builtin_exit(data, last_node);
	return (0);
}

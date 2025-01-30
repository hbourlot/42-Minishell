/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:04:19 by joralves          #+#    #+#             */
/*   Updated: 2025/01/29 01:05:04 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Removes specified environment variables from the shell.
/// @param data The shell structure containing environment mappings and state.
/// @param command_args The array of environment variable names to unset.
/// @return SUCCESS on successful removal, ERROR if an update operation fails.
/// @details Deletes the environment variables specified in `command_args` from the hashmap,
///          and then updates the environment variables and paths. Returns ERROR if updating
///          the environment fails.
int	builtin_unset(t_shell *data, char **command_args)
{
	int	i;

	i = 1;
	while (command_args[i])
	{
		hashmap_delete(data->map, command_args[i]);
		i++;
	}
	if (i > 1)
	{
		if (update_envp_and_envpath(data))
			return (ERROR);
	}
	data->exit_status = 0;
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:04:19 by joralves          #+#    #+#             */
/*   Updated: 2025/02/02 23:03:34 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Removes environment variables.
/// @param data The shell structure with mappings.
/// @param command_args The variable names to unset.
/// @return SUCCESS on removal, ERROR on failure.
/// @details Deletes variables from the hashmap and updates the environment.
///          Returns ERROR if updating fails. 
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:44:28 by joralves          #+#    #+#             */
/*   Updated: 2025/01/29 14:58:26 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_key_value(t_hashnode *current)
{
	while (current)
	{
		printf("%s", current->key);
		if (current->value)
			printf("=%s", current->value);
		printf("\n");
		current = current->next;
	}
}

/// @brief Displays the environment variables stored in the shell.
/// @param data The shell structure containing the environment hashmap.
/// @param command_args The array of arguments passed to the `env` command.
/// @details Prints all key-value pairs in the environment hashmap. If extra arguments 
///          are provided, an error message is displayed, and the exit status is set to 126. 
///          On success, the exit status is set to 0.
void	builtin_env(t_shell *data, char **command_args)
{
	int			idx;
	int			length;
	t_hashnode	*current;

	length = array_length(command_args);
	if (length > 1)
	{
		printf("env: '%s': Permission denied\n", command_args[1]);
		data->exit_status = 126;
		return ;
	}
	idx = 0;
	while (idx < HASHMAP_SIZE)
	{
		current = data->map->slots[idx];
		print_key_value(current);
		idx++;
	}
	data->exit_status = 0;
}

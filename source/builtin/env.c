/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:44:28 by joralves          #+#    #+#             */
/*   Updated: 2025/02/02 22:51:00 by joralves         ###   ########.fr       */
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

/// @brief Displays shell environment variables.
/// @param data The shell structure with the environment.
/// @param command_args The arguments array.
/// @details Prints all key-value pairs. Extra args cause an error (exit 126).  
///          On success, exit status is 0.
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

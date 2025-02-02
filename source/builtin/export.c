/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:11:13 by joralves          #+#    #+#             */
/*   Updated: 2025/02/02 22:54:36 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_key_value(t_hashmap *map)
{
	int			idx;
	t_hashnode	*current;

	idx = 0;
	while (idx < HASHMAP_SIZE)
	{
		current = map->slots[idx];
		while (current)
		{
			printf("declare -x %s", current->key);
			if (current->value)
				printf("=\"%s\"", current->value);
			printf("\n");
			current = current->next;
		}
		idx++;
	}
}

static int	add_new_variable_on_hashmap(t_shell *data, char *command_arg)
{
	char	*value;
	char	*temp_key;

	value = ft_strchr(command_arg, '=');
	if (!value)
	{
		if (hashmap_insert(data->map, command_arg, NULL) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	temp_key = ft_substr(command_arg, 0, value - command_arg);
	if (hashmap_insert(data->map, temp_key, value + 1) == ERROR)
		return (free(temp_key), ERROR);
	return (free(temp_key), 0);
}

/// @brief Handles the `export` command.
/// @param data The shell structure.
/// @param command_args The arguments array.
/// @details Prints variables if no args are given. Otherwise, adds new ones
///          and updates the environment. Returns 0 or ERROR.
int	builtin_export(t_shell *data, char **command_args)
{
	int	idx;
	int	length;

	idx = 1;
	length = array_length(command_args);
	if (length == 1)
	{
		print_key_value(data->map);
		data->exit_status = 0;
		return (0);
	}
	while (idx < length)
	{
		if (add_new_variable_on_hashmap(data, command_args[idx]) == ERROR)
			return (ERROR);
		idx++;
	}
	if (update_envp_and_envpath(data) == ERROR)
		return (ERROR);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:44:28 by joralves          #+#    #+#             */
/*   Updated: 2025/02/11 10:57:31 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_key_value(t_hashnode *current)
{
	while (current)
	{
		if (current->value)
		{
			printf("%s", current->key);
			printf("=%s", current->value);
			printf("\n");
		}
		current = current->next;
	}
}

static int	handle_env_errors(char *command_arg)
{
	int								i;
	int								result;
	// const t_access_check_function	checks_with_path[] = {check_is_directory,check_access_xok,
	// 	 check_access_fok, NULL};

	i = 0;
	result = 0;
	if (!command_arg)
		return (0);
	if(ft_strchr(command_arg, '/'))
	{
		result = check_is_directory(command_arg, ENV);
		if(!result)
			return (ft_printf_error("env: '%s': Not a directory\n", command_arg), 126);
		return (ft_printf_error("env: %s: Permission denied\n", command_arg), 126);
	}
	return (ft_printf_error("env: '%s': No such file or directory\n", command_arg),127);
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

	if (!data->env_paths)
	{
		ft_printf_error("bash: env: No such file or directory\n");
		data->exit_status = 127;
		return ;
	}
	length = array_length(command_args);
	if (length > 1)
	{
		data->exit_status = handle_env_errors(command_args[1]);
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

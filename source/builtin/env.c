/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:44:28 by joralves          #+#    #+#             */
/*   Updated: 2025/03/04 15:26:37 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_key_value(t_hashnode *current, int fd)
{
	while (current)
	{
		if (current->value)
			ft_printf_fd(fd, "%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

static int	handle_env_errors(char *command_arg)
{
	int	result;

	result = 0;
	if (!command_arg)
		return (0);
	if (ft_strchr(command_arg, '/'))
	{
		result = check_is_directory(command_arg, ENV);
		if (!result)
			return (ft_printf_fd(2, "env: '%s': Not a directory\n",
					command_arg), 126);
		return (ft_printf_fd(2, "env: %s: Permission denied\n", command_arg),
			126);
	}
	return (ft_printf_fd(2, "env: '%s': No such file or directory\n",
			command_arg), 127);
}

/// @brief Displays shell environment variables.
/// @param data The shell structure with the environment.
/// @param command_args The arguments array.
/// @details Prints all key-value pairs. Extra args cause an error (exit 126).
///          On success, exit status is 0.
void	builtin_env(t_shell *data, t_cmd *command, int fd)
{
	int			idx;
	int			length;
	t_hashnode	*current;

	if (!data->env_paths)
	{
		ft_printf_fd(2, "bash: env: No such file or directory\n");
		data->exit_status = 127;
		return ;
	}
	length = array_length(command->args);
	if (length > 1)
	{
		data->exit_status = handle_env_errors(command->args[1]);
		return ;
	}
	idx = 0;
	while (idx < HASHMAP_SIZE)
	{
		current = data->map->slots[idx];
		print_key_value(current, fd);
		idx++;
	}
	data->exit_status = 0;
}

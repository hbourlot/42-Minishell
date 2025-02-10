/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:44:28 by joralves          #+#    #+#             */
/*   Updated: 2025/02/10 17:15:51 by joralves         ###   ########.fr       */
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

// static int	check_is_directory(const char *path)
// {
// 	struct stat	stat_path;

// 	if (stat(path, &stat_path) != OK)
// 		return (0);
// 	if (S_ISDIR(stat_path.st_mode))
// 		return (ft_printf_error("bash: %s: is a directory\n", path), 127);
// 	return (0);
// }

static int	check_access_fok(t_shell *data, const char *path)
{
	if (access(path, F_OK) == 0)
		return (0);
	printf("bash: env: %s: No such file or directory\n", path);
	data->exit_status = 1;
	return (1);
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
		if (check_access_fok(data, command_args[1]) == 1)
			return ;
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

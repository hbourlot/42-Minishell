/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:57:27 by joralves          #+#    #+#             */
/*   Updated: 2025/01/27 17:18:05 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_access_fok(t_shell *data, const char *path)
{
	if (access(path, F_OK) == 0)
		return (0);
	printf("bash: cd: %s: No such file or directory\n", dir);
	data->exit_status = 1;
	return (1);
}

static int	change_directory(t_shell *data, const char *dir)
{
	t_hashmap	*map;
	char		cwd[PATH_MAX + 1];
	char		*temp_cwd;

	map = data->map;
	getcwd(cwd, PATH_MAX);
	if (check_access_fok(dir) != 0)
		return (1);
	if (chdir(dir) != 0)
	{
		printf("bash: cd: %s: Not a directory\n", dir);
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = 0;
	temp_cwd = ft_strdup(cwd);
	if (!temp_cwd)
		return (-1);
	hashmap_insert(map, "OLDPWD", temp_cwd);
	getcwd(cwd, PATH_MAX);
	temp_cwd = ft_strdup(cwd);
	if (!temp_cwd)
		return (-1);
	hashmap_insert(map, "PWD", temp_cwd);
	return (0);
}

/// @brief Changes the current directory using the `cd` command.
/// @param data The shell structure with environment mappings and state.
/// @param command_args Arguments passed to the `cd` command.
/// @return 0 on success, 1 on error, -1 on memory allocation failure.
/// @details Defaults to `HOME` if no arguments are provided, handles errors,
///     		and updates `PWD` and `OLDPWD` environment variables.
int	builtin_cd(t_shell *data, char **command_args)
{
	t_hashmap	*map;
	char		*home;
	size_t		arg_count;

	map = data->map;
	home = hashmap_search(map, "HOME");
	arg_count = array_length(command_args);
	if (arg_count == 1)
	{
		if (change_directory(data, home) == -1)
			return (-1);
	}
	else if (arg_count > 2)
	{
		printf("bash: cd: too many arguments\n");
		data->exit_status = 1;
		return (1);
	}
	if (change_directory(data, command_args[1]) == -1)
		return (-1);
	if (hashmap_to_env_array(data, map) == -1)
		return (-1);
	return (0);
}

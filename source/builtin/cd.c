/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:57:27 by joralves          #+#    #+#             */
/*   Updated: 2025/02/10 18:51:18 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	change_directory(t_shell *data, const char *dir)
{
	char	cwd[PATH_MAX + 1];
	char	*temp_cwd;

	getcwd(cwd, PATH_MAX);
	if (chdir(dir) != 0)
	{
		ft_printf_error("bash: cd: %s: Not a directory\n", dir);
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = 0;
	temp_cwd = ft_strdup(cwd);
	if (!temp_cwd)
		return (-1);
	if (hashmap_insert(data->map, "OLDPWD", temp_cwd) == ERROR)
		return (free(temp_cwd), -1);
	free(temp_cwd);
	getcwd(cwd, PATH_MAX);
	temp_cwd = ft_strdup(cwd);
	if (!temp_cwd)
		return (-1);
	if (hashmap_insert(data->map, "PWD", temp_cwd) == ERROR)
		return (free(temp_cwd), -1);
	free(temp_cwd);
	hashmap_to_env_array(data, data->map);
	return (0);
}

int	change_to_home_or_invalid_arg(t_shell *data, size_t arg_count)
{
	char	*home;

	if (arg_count == 1)
	{
		home = hashmap_search(data->map, "HOME");
		if (!home || !*home)
		{
			ft_printf_error("bash: cd: HOME not set\n");
			data->exit_status = 1;
			return (1);
		}
		if (change_directory(data, home) == -1)
			return (-1);
		return (0);
	}
	if (arg_count > 2)
	{
		printf("bash: cd: too many arguments\n");
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

int	change_to_oldpwd(t_shell *data)
{
	char	*oldpwd;

	oldpwd = hashmap_search(data->map, "OLDPWD");
	if (!oldpwd)
	{
		ft_printf_error("bash: cd: OLDPWD not set\n");
		data->exit_status = 1;
		return (1);
	}
	printf("%s\n", oldpwd);
	if (change_directory(data, oldpwd) == -1)
		return (-1);
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
	size_t	arg_count;
	int		exit_status;

	arg_count = array_length(command_args);
	if (arg_count == 1 || arg_count > 2)
	{
		if (change_to_home_or_invalid_arg(data, arg_count) == -1)
			return (-1);
		return (0);
	}
	if (ft_strcmp(command_args[1], "-") == 0)
	{
		if (change_to_oldpwd(data) == -1)
			return (-1);
		return (0);
	}
	if (check_access_fok(command_args[1], CD) != 0)
	{
		data->exit_status = 1;
		return (1);
	}
	if (change_directory(data, command_args[1]) == -1)
		return (-1);
	return (0);
}

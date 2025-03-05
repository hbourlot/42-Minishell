/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:09:31 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/05 17:34:53 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access_fok(const char *path, int code)
{
	if (access(path, F_OK) == OK)
		return (0);
	if (code == ENV)
		return (127);
	return (ft_printf_fd(2, "bash: %s: No such file or directory\n", path),
		127);
}

int	check_access_xok(const char *path, int code)
{
	if (access(path, X_OK) == OK)
		return (0);
	if (code == ENV)
		return (126);
	return (ft_printf_fd(2, "bash: %s: Permission denied\n", path), 126);
}

int	check_is_directory(const char *path, int code)
{
	struct stat	stat_path;

	if (stat(path, &stat_path) != OK)
		return (0);
	if (S_ISDIR(stat_path.st_mode))
	{
		if (code == ENV)
			return (127);
		return (ft_printf_fd(2, "bash: %s: is a directory\n", path), 127);
	}
	return (0);
}

int	validate_command_path_access(char *command_path)
{
	int								i;
	int								result;
	const t_access_check_function	checks_with_path[] = {check_access_fok,
		check_is_directory, check_access_xok, NULL};

	i = 0;
	result = 0;
	if (!command_path)
		return (0);
	if (ft_strrchr(command_path, '/'))
	{
		while (checks_with_path[i] != NULL)
		{
			result = checks_with_path[i](command_path, 0);
			if (result)
				return (result);
			i++;
		}
	}
	else
		return (ft_printf_fd(2, "bash: %s: command not found\n", command_path),
			127);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:09:31 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/12 15:29:32 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access_fok(const char *path)
{
	if (access(path, F_OK) == OK)
		return (0);
	return (ft_printf_error("bash: %s: No such file or directory\n", path),
		127);
}

static int	check_access_xok(const char *path)
{
	if (access(path, X_OK) == OK)
		return (0);
	return (ft_printf_error("bash: %s: Permission denied\n", path), 126);
}

static int	ft_is_directory(const char *path)
{
	struct stat	stat_path;

	if (stat(path, &stat_path) != OK)
		return (0);
	return (S_ISDIR(stat_path.st_mode));
}

static int	check_is_directory(const char *path)
{
	struct stat	stat_path;

	if (stat(path, &stat_path) != OK)
		return (0);
	if (S_ISDIR(stat_path.st_mode))
		return (ft_printf_error("bash: %s: is a directory\n", path), 127);
	return (0);
}

int	parsing_command_path_execution(char *command_path)
{
	int			i;
	int			result;
	const int	(*checks_with_path[])(const char *) = {check_access_fok,
		check_is_directory, check_access_xok, NULL};

	i = 0;
	result = 0;
	if (!command_path)
		return (0);
	if (ft_strrchr(command_path, '/'))
	{
		while (checks_with_path[i] != NULL)
		{
			result = checks_with_path[i](command_path);
			if (result)
				return (result);
			i++;
		}
	}
	else
		return (ft_printf_error("bash: %s: command not found\n", command_path),
			127);
	return (0);
}

// const t_access_check_function	checks_with_path[] = {check_access_fok,
// 	check_is_directory, check_access_xok, NULL};
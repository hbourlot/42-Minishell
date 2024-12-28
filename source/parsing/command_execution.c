/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:09:31 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/28 18:28:43 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Parses and validates file redirection paths for read/write access.
/// @param redir_files The linked list of file redirection.
/// @return 0 on success, or 1 on failure with an error message.
int	parsing_file_read_execution(t_file *redir_files)
{
	while (redir_files && redir_files->read)
	{
		if (redir_files->read)
		{
			if (access(redir_files->read, F_OK) != OK)
				return (ft_printf_error("bash: %s: No such file or directory\n",
						redir_files->read), 1);
			else if (access(redir_files->read, R_OK) != OK
				|| access(redir_files->read, W_OK) != OK)
				return (ft_printf_error("bash: %s: Permission denied\n",
						redir_files->read), 1);
			redir_files = redir_files->next;
		}
	}
	return (0);
}

/// @brief Validates the existence and permissions of a command path.
/// @param command_path The full path to the command.
/// @return 0 on success, or an error code on failure
///				(127 for not found, 126 for permission denied).
int	parsing_command_path_execution(char *command_path)
{
	if (command_path)
	{
		if (!ft_strrchr(command_path, '/'))
			return (ft_printf_error("bash: %s: command not found\n", command_path), 127);
		if (access(command_path, F_OK) != OK)
		{
			return (ft_printf_error("bash: %s: No such file or directory\n",
					command_path), 127);
		}
		if (access(command_path, X_OK) == OK)
			return (0);
		else if (access(command_path, R_OK) != OK || access(command_path, W_OK) != OK
			|| access(command_path, X_OK))
		{
			return (ft_printf_error("bash: %s: Permission denied\n", command_path),
				126);
		}	
	}	
	return (0);
}

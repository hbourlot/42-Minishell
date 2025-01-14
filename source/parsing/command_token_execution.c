/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_token_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:55:05 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/12 15:28:21 by hbourlot         ###   ########.fr       */
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

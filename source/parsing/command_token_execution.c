/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_token_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:55:05 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/18 16:05:22 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Parses and validates file redirection paths for read/write access.
/// @param rf The linked list of file redirection.
/// @return 0 on success, or 1 on failure with an error message.
int	validate_file_read_execution(t_file *rf)
{
	while (rf && rf->read)
	{
		if (rf->read)
		{
			if (access(rf->read, F_OK) != OK)
				return (ft_printf_fd(2, "bash: %s: No such file or directory\n",
						rf->read), 1);
			else if (access(rf->read, R_OK) != OK || access(rf->read,
					W_OK) != OK)
				return (ft_printf_fd(2, "bash: %s: Permission denied\n",
						rf->read), 1);
			rf = rf->next;
		}
	}
	return (0);
}

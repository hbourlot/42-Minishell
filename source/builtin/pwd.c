/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:22 by joralves          #+#    #+#             */
/*   Updated: 2025/02/02 23:02:08 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Implements the `pwd` built-in command.  
/// @param data The shell structure with environment and state.  
/// @details Retrieves the current directory with `getcwd` and prints it.  
///          Sets `exit_status` to 0 on success.  
void	builtin_pwd(t_shell *data)
{
	char	cwd[PATH_MAX + 1];

	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	data->exit_status = 0;
}

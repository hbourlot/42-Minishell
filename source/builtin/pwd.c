/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:22 by joralves          #+#    #+#             */
/*   Updated: 2025/01/30 15:46:30 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Implements the `pwd` built-in command to print the current working directory.
/// @param data The shell structure containing environment and state.
/// @details Retrieves the current working directory using `getcwd` and prints it.
///          Sets `exit_status` to 0 upon successful execution.
void	builtin_pwd(t_shell *data)
{
	char	cwd[PATH_MAX + 1];

	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	data->exit_status = 0;
}

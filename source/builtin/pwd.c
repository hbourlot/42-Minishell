/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:23:22 by joralves          #+#    #+#             */
/*   Updated: 2025/01/28 16:04:48 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(t_shell *data)
{
	char cwd[PATH_MAX + 1];

	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	data->exit_status = 0;
}

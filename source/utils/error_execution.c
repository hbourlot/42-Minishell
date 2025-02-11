/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_execution.c                                  :+:      :+:    :+:   */
/*                                             p       +:+ +:+
	+:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:40:33 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/29 08:40:15 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error_ex(void)
{
	t_error	*error;
	int		code;

	error = get_error_context();
	code = error->code;
	if (error->execution.folder && error->execution.msg)
		ft_printf_error("bash: %s: %s\n", error->execution.folder,
			error->execution.msg);
	else if (error->execution.msg)
		ft_printf_error("bash: %s: Initialization failed\n",
			error->execution.msg);
	return (code);
}

void	set_error_ex(int code, char *msg, const char *folder, bool exit)
{
	t_error	*error;

	error = get_error_context();
	error->execution.is_initialized = true;
	if (code)
		error->code = code;
	if (msg)
		error->execution.msg = msg;
	if (folder)
		error->execution.folder = (char *)folder;
	if (exit)
		error->exit = true;
}

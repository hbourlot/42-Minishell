/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:21:00 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 22:45:48 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error_in(void)
{
	t_error	*error;
	int		code;

	error = get_error_context();
	code = error->code;
	if (error->initialize.msg && error->initialize.function)
	{
		ft_printf_error("Error: %s in function: %s\n", error->initialize.msg,
			error->initialize.function);
	}
	return (code);
}

void	set_error_in(int code, char *msg, const char *function,
		bool exit)
{
	(void)code;

	t_error	*error;

	error = get_error_context();
	error->initialize.is_initialized = true;
	if (msg)
		error->initialize.msg = msg;
	if (function)
		error->initialize.function = (char *)function;
	if (exit)
		error->exit = exit;
}

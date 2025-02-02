/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:32:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 22:45:30 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error_pa(void)
{
	t_error	*error;
	int		code;

	error = get_error_context();
	code = error->code;
	if (error->parsing.token)
	{
		ft_putstr_fd(SYNTAX_ERROR_MSG, 2);
		ft_putstr_fd(error->parsing.token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error->parsing.syntax && error->parsing.function)
	{
		ft_printf_error("Error: %s in function: %s\n", error->parsing.syntax,
			error->parsing.function);
	}
	return (code);
}

void	set_error_pa(int code, char *syntax, char *token,
		const char *function)
{
	(void)code;
	t_error	*error;

	error = get_error_context();
	error->parsing.is_initialized = true;
	if (syntax)
		error->parsing.syntax = syntax;
	if (token)
		error->parsing.token = token;
	if (function)
		error->parsing.function = (char *)function;
}

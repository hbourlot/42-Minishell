/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:32:37 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 16:02:52 by joralves         ###   ########.fr       */
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
		ft_putstr_fd(error->parsing.syntax, 2);
		ft_putstr_fd(error->parsing.token, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (code);
}

void	set_error_pa(int code, char *syntax, char *token)
{
	t_error	*error;

	(void)code;
	error = get_error_context();
	error->parsing.is_initialized = true;
	if (syntax)
		error->parsing.syntax = syntax;
	if (token)
		error->parsing.token = token;
}

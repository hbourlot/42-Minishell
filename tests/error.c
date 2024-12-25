/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:41:15 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 11:21:39 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static t_error *error_context(void)
{
	static t_error error;
	return (&error);
}

void reset_error(t_error *error)
{
	error->code = 0;
	error->message = NULL;
	error->function = NULL;
}

int handle_error(void)
{
	t_error *error;
	
	error = error_context();
	if (error->token)
	{
		ft_putstr_fd(SYNTAX_ERROR_MSG, 2);
		ft_putstr_fd(error->token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error->message)
	{
		fprintf(stderr, "Error: %s in function: %s\n", error->message, error->function);
		reset_error(error);
	}
	return (error->code);
}
void set_error(int code, const char *message, char *token, const char *function) 
{
	t_error *error;
	
	error = error_context();
    error->code = code;
	error->token = token;
    error->message = (char *)message;
    error->function = (char *)function;
}

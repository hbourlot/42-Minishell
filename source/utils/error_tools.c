/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:10:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/11 13:23:39 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Provides a static error context shared
///				across functions. This allows centralizing
///				error handling in one place.
/// @return A pointer to the static t_error structure.
t_error	*get_error_context(void)
{
	static t_error	error;

	return (&error);
}

/// @brief Resets the error context by clearing its fields.
/// @param error Pointer to the error context to reset.
void	reset_error_context(t_error *error)
{
	ft_memset(error, 0, sizeof(t_error));
}

int	handle_error(void)
{
	t_error	*error;
	int		code;

	error = get_error_context();
	code = error->code;
	if (error->parsing.is_initialized)
		code = handle_error_parsing();
	else if (error->initialize.is_initialized)
		code = handle_error_initialize();
	else if (error->execution.is_initialized)
		code = handle_error_execution();
	if (error->exit == true)
	{
		cleanup_shell(get_shell());
		exit(code);
	}
	reset_error_context(error);
	return (code);
}

/// @brief Handles and prints the current error context.
///        	It displays syntax errors or generic errors
///				based on the context.
/// @return The current error code.
// int	handle_error(void)
// {
// 	t_error	*error;
// 	int		code;

// 	error = error_context();
// 	code = error->code;
// 	// if (error->archive)
// 	// {
// 	// 	perror(error->archive);
// 	// }
// 	if (error->token)
// 	{
// 		ft_putstr_fd(SYNTAX_ERROR_MSG, 2);
// 		ft_putstr_fd(error->token, 2);
// 		ft_putstr_fd("'\n", 2);
// 	}
// 	else if (error->message)
// 	{
// 		fprintf(stderr, "Error: %s in function: %s\n", error->message,
// 			error->function);
// 		reset_error(error);
// 	}
// 	reset_error(error);
// 	return (code);
// }

/// @brief Sets an error in the error context with the provided details.
/// @param code The error code to set.
/// @param message A string describing the error.
/// @param token The problematic token (if applicable).
/// @param function The name of the function where the error occurred.
// void	set_error(int code, const char *message, char *token,
// 		const char *function)
// {
// 	t_error	*error;

// 	error = error_context();
// 	error->code = code;
// 	error->token = token;
// 	error->message = (char *)message;
// 	error->function = (char *)function;
// }

// void	set_error_runner(int code, char *archive)
// {
// 	t_error	*error;

// 	error = error_context();
// 	if (archive)
// 		error->archive = archive;
// }
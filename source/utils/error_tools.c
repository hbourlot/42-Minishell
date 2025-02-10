/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:10:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 15:18:48 by hbourlot         ###   ########.fr       */
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


static int	set_error(int error, const char *token, const char *func)
{
	if (error == E_SYNTAX_NEWLINE)
		set_error_pa(2, SYNTAX_ERROR_MSG, "newline");
	else if (error == E_SYNTAX_TOKEN)
		set_error_pa(2, SYNTAX_ERROR_MSG, (char *)token);
	else if (error == E_SHELL_SUPPORT)
		set_error_pa(2, NO_SUPPORT_MSG, (char *)token);
	else if (error == E_MALLOC)
		set_error_in(1, "\"Malloc\"", func, true);
	else if (error == E_PF)
		set_error_ex(1, "Pipe/Fork", NULL, false);
	else if (error == E_VFRE)
		set_error_ex(1, NULL, NULL, true);
	else if (error == E_FILE_DIR)
		set_error_ex(1, NO_FILE_DIR_MSG, token, true);
	else if (error == 127 || error == 126)
		set_error_ex(error, NULL, NULL, true);
}

int	handle_error(int error, const char *token, const char *func)
{
	t_error	*s_error;
	int		code;

	set_error(error, token, func);
	s_error = get_error_context();
	code = s_error->code;
	if (s_error->parsing.is_initialized)
		code = handle_error_pa();
	else if (s_error->initialize.is_initialized)
		code = handle_error_in();
	else if (s_error->execution.is_initialized)
		code = handle_error_ex();
	if (s_error->exit == true)
	{
		cleanup_shell(get_shell());
		exit(code);
	}
	reset_error_context(s_error);
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
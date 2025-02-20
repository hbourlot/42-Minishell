/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:10:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/11 00:04:31 by joralves         ###   ########.fr       */
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

static void	set_error(int error, const char *token, const char *func)
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

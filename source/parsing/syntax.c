/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/04 10:13:27 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Parses the input string to validate its syntax.
///        Specifically checks for invalid token sequences
///         and reports syntax errors.
/// @param input The input string to parse.
/// @return 0 if the input is valid; -1 if a syntax error is detected.
int	parsing_syntax(char *input)
{
	const char *pipe_tokens[] = {"||", "|", NULL};
	const char *redirect_tokens[] = {"<<", ">>", ">", "<", NULL};

	// if (is_valid_tokens(input, pipe_tokens, redirect_tokens))
	// 	return (-1);
	if (is_valid_pipe_tokens(input) == false)
		return (-1);
	if (is_valid_file_and_here_doc_tokens(input) == false)
		return (-1);
	return (0);
}

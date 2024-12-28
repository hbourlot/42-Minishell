/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:52 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/28 15:28:57 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Checks if the sequence of tokens in the input string is valid.
///        Ensures that no invalid sequences like 
///        "||", "| >", or "| end-of-input" occur.
/// @param input The input string to validate.
/// @param tokens The array of token strings to check for in the input.
/// @return True if the token sequence is valid; false otherwise.
static bool	is_valid_token_sequence(char *input, const char *tokens[])
{
	size_t	len;
	int		idx;
	char	*source;

	source = input;
	if (is_valid_pipe_redirects_tokens(source, len, idx, tokens) == false)
		return (false);
	// while (source)
	// {
	// 	source = ft_strstr_any(source, tokens);
	// 	if (source && find_string_match(source, tokens, &idx) == OK)
	// 	{
	// 		len = ft_strlen(tokens[idx]);
	// 		source += len;
	// 		while (*source && *source == ' ')
	// 			source++;
	// 		if (!*source || find_string_match(source, tokens, &idx) == OK)
	// 		{
	// 			if (!*source)
	// 				return (set_error_parsing(2, SYNTAX_ERROR_MSG, "newline", __func__),
	// 					false);
	// 			return (set_error_parsing(2, SYNTAX_ERROR_MSG, (char *)tokens[idx],
	// 					__func__), false);
	// 		}
	// 	}
	// }
	return (true);
}

/// @brief Parses the input string to validate its syntax.
///        Specifically checks for invalid token sequences
///         and reports syntax errors.
/// @param input The input string to parse.
/// @return 0 if the input is valid; -1 if a syntax error is detected.
int	parsing_syntax(char *input)
{
	const char	*tokens[] = {"|", "||", "&&", ">", ">>", "<", "<<", NULL};

	sort_strings_by_length_desc((char **)tokens);
	if (is_valid_token_sequence(input, tokens) == false)
		return (ERROR);
	return (SUCCESS);
}

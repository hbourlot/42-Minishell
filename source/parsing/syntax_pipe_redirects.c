/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:21:13 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/14 15:29:44 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_file_and_here_doc_tokens(char *source)
{
	const char	*tokens[] = {"<<", ">>", ">", "<", NULL};
	const char	*pipe_tokens[] = {"||", "|", NULL};
	int			idx;

	idx = 0;
	while (source)
	{
		source = ft_strstr_any(source, tokens);
		if (source && find_string_match(source, tokens, &idx) == OK)
		{
			source += ft_strlen(tokens[idx]);
			skip_spaces(&source);
			if (find_string_match(source, pipe_tokens, &idx) == OK)
				return (set_error_parsing(1, SYNTAX_ERROR_MSG,
						(char *)pipe_tokens[idx], __func__), false);
			if (!*source)
				return (set_error_parsing(1, SYNTAX_ERROR_MSG, "newline",
						__func__), false);
			if (find_string_match(source, tokens, &idx) == OK)
				return (set_error_parsing(1, SYNTAX_ERROR_MSG,
						(char *)tokens[idx], __func__), false);
			else
				continue ;
		}
	}
	return (true);
}

static bool	is_first_pipe_token_valid(char *source, const char *tokens[])
{
	size_t	length;
	char	*tmp;
	int		idx;

	length = 0;
	tmp = ft_strstr_any(source, tokens);
	if (!tmp)
		return (true);
	length = tmp - source;
	while (length && length--)
	{
		if (*source && *source == ' ')
			source++;
		if (*source && *source != ' ')
			break ;
	}
	if (length)
		return (true);
	find_string_match(tmp, tokens, &idx);
	set_error_parsing(1, SYNTAX_ERROR_MSG, (char *)tokens[idx], __func__);
	return (false);
}

bool	is_valid_pipe_tokens(char *source)
{
	int			idx;
	const char	*pipe_tokens[] = {"||", "|", NULL};

	idx = 0;
	if (is_first_pipe_token_valid(source, pipe_tokens) == false)
		return (false);
	while (source && *source)
	{
		source = ft_strstr_any(source, pipe_tokens);
		if (source && *source && find_string_match(source, pipe_tokens,
				&idx) == OK)
		{
			source += ft_strlen(pipe_tokens[idx]);
			skip_spaces(&source);
			if (*source && find_string_match(source, pipe_tokens, &idx) == OK)
				// If has and its another pipe ERROR CASE
				return (set_error_parsing(2, SYNTAX_ERROR_MSG,
						(char *)pipe_tokens[idx], __func__), false);
			if (*source && ft_strcmps(source, pipe_tokens) == ERROR)
				// If has and it's not another pipe
				continue ;                                           
					// Right case
			if (!*source)
			{
				get_shell()->it_ends_with_single_pipe = true;
				// TODO: might be here_doc, still need to parsing << |
				printf("HERE_DOC TO append com command list\n");
					// HERE_DOC CASE
				continue ;
			}
		}
	}
	return (true);
}

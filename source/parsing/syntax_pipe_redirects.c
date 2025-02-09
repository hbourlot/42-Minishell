/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:21:13 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/09 21:38:39 by hbourlot         ###   ########.fr       */
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
			while (*source && *source == REP_SPACE)
				source++;
			if (find_string_match(source, pipe_tokens, &idx) == OK)
				return (set_error_pa(1, SYNTAX_ERROR_MSG,
						(char *)pipe_tokens[idx]), false);
			if (!*source)
				return (set_error_pa(1, SYNTAX_ERROR_MSG, "newline"), false);
			if (find_string_match(source, tokens, &idx) == OK)
				return (set_error_pa(1, SYNTAX_ERROR_MSG,
						(char *)tokens[idx]), false);
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
		if (*source && *source == REP_SPACE)
			source++;
		if (*source && *source != REP_SPACE)
			break ;
	}
	if (length)
		return (true);
	find_string_match(tmp, tokens, &idx);
	set_error_pa(1, SYNTAX_ERROR_MSG, (char *)tokens[idx]);
	return (false);
}



bool	is_valid_pipe_tokens(char *source)
{
	int			idx;
	const char	*deli_tokens[] = {"&&", "||", "|", NULL};

	idx = 0;
	if (is_first_pipe_token_valid(source, deli_tokens) == false)
		return (false);
	while (source && *source)
	{
		source = ft_strstr_any(source, deli_tokens);
		if (source && *source && find_string_match(source, deli_tokens,
				&idx) == OK)
		{
			source += ft_strlen(deli_tokens[idx]);
			skip_spaces(&source);
			if (*source && find_string_match(source, deli_tokens, &idx) == OK)
				// If has and its another pipe ERROR CASE
				return (set_error_pa(2, SYNTAX_ERROR_MSG, (char *)deli_tokens[idx]), false);
			if (*source && ft_strcmps(source, deli_tokens) == ERROR)
				// If has and it's not another pipe
				continue ;                    
				// Right case
			if (!*source)
			{
				get_shell()->it_ends_with_delimiter = true;
				// TODO: might be here_doc, still need to parsing << |
				printf("HERE_DOC TO append com command list\n");
					// HERE_DOC CASE
				continue ;
			}
		}
	}
	return (true);
}


static bool get_file_redirects_errors(char *rl, int *i, int length)
{
	const char	*deli_tokens[] = {"&&", "||", "|", NULL};
	const char  *file_tokens[] = {"<<", ">>", "<", ">", NULL};
	int			idx;

	*i += length;
	while (rl[*i] && rl[*i] == REP_SPACE)
		(*i)++;
	if (rl[*i] == '\0')
		return (handle_error(E_SYNTAX_NEWLINE, "newline", NULL), true);
	else if (find_string_match(&rl[*i], file_tokens, &idx) == OK)
		return (handle_error(E_SYNTAX_TOKEN, (char *)file_tokens[idx], NULL), true);
	else if (find_string_match(&rl[*i], deli_tokens, &idx) == OK)
		return (handle_error(E_SYNTAX_TOKEN, (char *)deli_tokens[idx], NULL), true);

	return (false);	
}

static bool get_syntax_errors(char *rl, int *i, int length)
{
	const char	*deli_tokens[] = {"&&", "||", "|", NULL};
	const char  *file_tokens[] = {"<<", ">>", "<", ">", NULL};
	int			idx;


	if (find_string_match(&rl[*i], file_tokens, &idx) == OK)
	{
		length = ft_strlen(file_tokens[idx]);
		return (get_file_redirects_errors(rl, i, length));
	}
	*i += length;
	while (rl[*i] && rl[*i] == REP_SPACE)
		(*i)++;
	if (rl[*i] == '\0')
		return (handle_error(E_SHELL_SUPPORT, NULL, __func__), true);
	else if (rl[*i] && find_string_match(&rl[*i], deli_tokens, &idx) == OK)
		return (handle_error(E_SYNTAX_TOKEN, (char *)deli_tokens[idx], __func__), true);
	else if (rl[*i] && find_string_match(&rl[*i], file_tokens, &idx) == OK)
		return (get_file_redirects_errors(rl, i, ft_strlen(file_tokens[idx])));

	return (false);
}


bool is_tokens_invalid(char *rl)
{
	int			i;
	int			idx;
	bool		in_quotes;
	const char	*deli_tokens[] = {"&&", "||", "|", NULL};
	const char  *file_tokens[] = {"<<", ">>", "<", ">", NULL};

	i = 0;
	in_quotes = false;
	if (find_string_match(&rl[i], deli_tokens, &idx) == OK && i == 0)
		return (handle_error(E_SYNTAX_TOKEN, (char *)deli_tokens[idx], NULL), true);
	while (rl[i])
	{
		while (rl[i] == REP_SPACE)
			i++;
		if (rl[i] == 1 || rl[i] == 2)
			in_quotes = !in_quotes;
		else if ( !in_quotes && (find_string_match(&rl[i], deli_tokens, &idx) == OK
			|| find_string_match(&rl[i], file_tokens, &idx) == OK ))
		{
			if (get_syntax_errors(rl, &i, ft_strlen(deli_tokens[idx])))
				return (true);
		}
		i++;
	}
}

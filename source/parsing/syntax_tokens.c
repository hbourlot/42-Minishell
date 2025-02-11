/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:21:13 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/11 00:13:39 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	get_file_redirects_errors(char *rl, int *i, int length)
{
	const char	*deli_tokens[] = {"&&", "||", "|", NULL};
	const char	*file_tokens[] = {"<<", ">>", "<", ">", NULL};
	int			idx;

	*i += length;
	while (rl[*i] && rl[*i] == REP_SPACE)
		(*i)++;
	if (rl[*i] == '\0')
		return (handle_error(E_SYNTAX_NEWLINE, "newline", NULL), true);
	else if (find_string_match(&rl[*i], file_tokens, &idx) == OK)
		return (handle_error(E_SYNTAX_TOKEN, (char *)file_tokens[idx], NULL),
			true);
	else if (find_string_match(&rl[*i], deli_tokens, &idx) == OK)
		return (handle_error(E_SYNTAX_TOKEN, (char *)deli_tokens[idx], NULL),
			true);
	return (false);
}

static bool	get_syntax_errors(char *rl, int *i, int length, int prev_idx)
{
	const char	*deli_tokens[] = {"&&", "||", "|", NULL};
	const char	*file_tokens[] = {"<<", ">>", "<", ">", NULL};
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
		return (handle_error(E_SHELL_SUPPORT, (char *)deli_tokens[prev_idx],
				__func__), true);
	else if (rl[*i] && find_string_match(&rl[*i], deli_tokens, &idx) == OK)
		return (handle_error(E_SYNTAX_TOKEN, (char *)deli_tokens[idx],
				__func__), true);
	else if (rl[*i] && find_string_match(&rl[*i], file_tokens, &idx) == OK)
		return (get_file_redirects_errors(rl, i, ft_strlen(file_tokens[idx])));
	return (false);
}

static bool	check_initial_token_error(char *rl, const char **deli_tokens)
{
	int	idx;

	if (find_string_match(rl, deli_tokens, &idx) == OK)
	{
		handle_error(E_SYNTAX_TOKEN, (char *)deli_tokens[idx], NULL);
		return (true);
	}
	return (false);
}

static void	toggle_quotes(char *rl, bool *in_quotes, int i)
{
	if (rl[i] == 1 || rl[i] == 2)
		*in_quotes = !*in_quotes;
}

bool	is_tokens_invalid(char *rl)
{
	int			i;
	int			idx;
	bool		in_quotes;
	const char	*deli_tokens[] = {"&&", "||", "|", NULL};
	const char	*file_tokens[] = {"<<", ">>", "<", ">", NULL};

	i = 0;
	in_quotes = false;
	if (check_initial_token_error(&rl[i], deli_tokens))
		return (true);
	while (rl && rl[i])
	{
		skip_character_by_idx(rl, REP_SPACE, &i);
		toggle_quotes(rl, &in_quotes, i);
		if (!in_quotes && (find_string_match(&rl[i], deli_tokens, &idx) == OK
				|| find_string_match(&rl[i], file_tokens, &idx) == OK))
		{
			if (get_syntax_errors(rl, &i, ft_strlen(deli_tokens[idx]), idx))
				return (true);
		}
		if (rl[i] == '\0')
			break ;
		i++;
	}
	return (false);
}

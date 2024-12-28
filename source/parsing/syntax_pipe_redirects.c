/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipe_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:21:13 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/28 15:29:15 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static bool handle_error_syntax(char *source, const char *tokens[], int idx)
{
	int	idx_redirects;

	const char *redirects[] = {">", ">>", "<<", "<", NULL};

	sort_strings_by_length_desc((char **)redirects);
	if (!*source || find_string_match(source, redirects, &idx_redirects) == OK)
		return (set_error_parsing(2, SYNTAX_ERROR_MSG, "newline", __func__),
			false);
	return (set_error_parsing(2, SYNTAX_ERROR_MSG, (char *)tokens[idx],
			__func__), false);
}

// static bool not_in_token_case(t_shell *data)
// {
		
// }

bool is_valid_pipe_redirects_tokens(char *source, size_t len, int idx, const char *tokens[])
{
	bool	in_token;

	in_token = false;	
	while (source)
	{
		source = ft_strstr_any(source, tokens);
		in_token = !in_token;
		if (source && find_string_match(source, tokens, &idx) == OK)
		{
			len = ft_strlen(tokens[idx]);
			source += len;
			while (*source && *source == ' ')
				source++;
			if (*source && find_string_match(source, tokens, &idx) == ERROR)
				in_token = false;
			if (in_token && !*source)
			{
				printf("HERE_DOC CASE\n");	
				printf("IN_TOKEN MAS ACABOU COM NADA\n");
			}
			else if (in_token && (!*source || find_string_match(source, tokens, &idx) == OK))
				return (handle_error_syntax(source, tokens, idx));
			else if (!in_token && !*source)
				printf("HERE_DOC CASE\n");
		}
	}
	return (true);
}
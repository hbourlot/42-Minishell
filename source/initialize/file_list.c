/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:31:14 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/06 16:23:47 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_file(char *input, int *position, t_token token,
		t_file **redir_files)
{
	t_file	*new;
	t_file	*current;
	char	*src;

	new = ft_calloc(1, sizeof(t_file));
	if (!new)
		return (-1);
	src = ft_substr(input, position[0], position[1] - position[0]);
	if (!src)
		return (-1);
	new->redirect = token;
	if (token == REDIRECT_LEFT_SINGLE)
		new->read = src;
	else if (token == REDIRECT_RIGHT_SINGLE || token == REDIRECT_RIGHT_DOUBLE)
		new->write = src;
	current = *redir_files;
	if (!current)
		*redir_files = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

int	initialize_file_list(char *input, const char *redirects[],
		t_file **redir_files)
{
	int		idx;
	int		position[2];
	t_token	token;
	bool	in_quotes;

	in_quotes = false;
	while (input && *input)
	{
		if (*input && (*input == REP_DOUBLE_QUOTE
				|| *input == REP_SINGLE_QUOTE))
			in_quotes = !in_quotes;
		else if (!in_quotes && find_string_match(input, redirects, &idx) == OK)
		{
			token = get_t_token(input, ft_strlen(redirects[idx]));
			get_redirect_complement(input, &position[0], &position[1],
				ft_strlen(redirects[idx]));
			if (add_file(input, position, token, redir_files) < 0)
				return (-1);
		}
		input++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:31:14 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/19 14:22:24 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_file_to_list(t_file **file, t_file *new_file)
{
	t_file	*last;


	if (!(*file))
		*file = new_file;
	else
	{
		last = *file;
		while (last->next)
			last = last->next;
		last->next = new_file;
	}
}

static int init_file(t_file *rf, char *input, int *pos, t_token token)
{
	char *src;

	src = ft_substr(input, pos[0], pos[1] - pos[0]);
	if (!src)
		return (-1);
	rf->redirect = token;
	if (token == REDIRECT_LEFT_DOUBLE || token == REDIRECT_LEFT_SINGLE)
		rf->read = src;
	else
		rf->write = src;
	truncate_character(src, REP_DQ);
	truncate_character(src, REP_SQ);
	return 0;
}

static int	add_file(t_cmd *command, char *input, int *pos, t_token token)
{
	t_file	*new;
	char	*src;

	new = ft_calloc(1, sizeof(t_file));
	if (!new)
		return (-1);
	if (init_file(new, input, pos, token))
		return (free(new), -1);
	if (new->redirect == REDIRECT_LEFT_DOUBLE)
		add_file_to_list(&command->eof_rf, new);
	else
		add_file_to_list(&command->io_rf, new);
	return (0);
}

int	initialize_file_list(t_cmd *command, const char *redirects[])
{
	int		i;
	int		idx;
	int		pos[2];
	t_token	token;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	sort_strings_by_length_desc((char **)redirects);
	while (command->input_expanded && command->input_expanded[i])
	{
		if (command->input_expanded[i] && (command->input_expanded[i] == REP_DQ || command->input_expanded[i] == REP_SQ))
			in_quotes = !in_quotes;
		else if (!in_quotes && find_string_match(&command->input_expanded[i], redirects, &idx) == OK)
		{
			token = get_t_token(&command->input_expanded[i], ft_strlen(redirects[idx]));
			get_redirect_complement(&command->input_expanded[i], &pos[0], &pos[1],
				ft_strlen(redirects[idx]));
			if (add_file(command, &command->input_expanded[i], pos, token) < 0)
				return (-1);
			i += ft_strlen(redirects[idx]);
			if (command->input_expanded[i] == '\0')
				break;
		}
		i++;
	}
	return (0);
}

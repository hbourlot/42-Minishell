/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:31:14 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/21 14:36:33 by joralves         ###   ########.fr       */
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

static int	init_file(t_file *rf, char *input, int *pos, t_token token)
{
	char	*src;

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
	return (0);
}

static int	add_file(t_cmd *command, char *input, int *pos, t_token token)
{
	t_file	*new;

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

int	token_aux(t_cmd *cmd, const char *redirects[], int *i, int *idx)
{
	t_token	token;
	int		pos[2];

	token = get_t_token(&cmd->input_expanded[*i], ft_strlen(redirects[*idx]));
	get_redirect_complement(&cmd->input_expanded[*i], &pos[0], &pos[1],
		ft_strlen(redirects[*idx]));
	if (add_file(cmd, &cmd->input_expanded[*i], pos, token) < 0)
		return (-1);
	*i += ft_strlen(redirects[*idx]);
	return (0);
}

int	initialize_file_list(t_cmd *cmd, const char *redirects[])
{
	int		i;
	bool	in_quotes;
	int		idx;

	i = 0;
	in_quotes = false;
	sort_strings_by_length_desc((char **)redirects);
	while (cmd->input_expanded && cmd->input_expanded[i])
	{
		if (cmd->input_expanded[i] && (cmd->input_expanded[i] == REP_DQ
				|| cmd->input_expanded[i] == REP_SQ))
			in_quotes = !in_quotes;
		else if (!in_quotes && find_string_match(&cmd->input_expanded[i],
				redirects, &idx) == OK)
		{
			if (token_aux(cmd, redirects, &i, &idx))
				return(-1);
			if (cmd->input_expanded[i] == '\0')
				break ;
		}
		i++;
	}
	return (0);
}

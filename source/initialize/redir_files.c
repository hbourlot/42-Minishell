/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:31:14 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/08 14:58:01 by hbourlot         ###   ########.fr       */
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

static void	heredoc_expansion(t_file *rf, char *src)
{
	int		start;
	int		end;
	int		j;
	char	*temp;

	j = 2;
	while (src[j] == REP_SPACE)
		j++;
	start = j;
	while (src[j] && src[j] != REP_SPACE)
		j++;
	end = j;
	temp = ft_substr(src, start, end - start);
	if (!temp)
		handle_error(E_MALLOC, NULL, __func__);
	if (ft_strchr(temp, REP_DQ) || ft_strchr(temp, REP_SQ))
		rf->in_quotes = true;
	free(temp);
}

static int	init_file(t_file *rf, char *input, int *pos, t_token token)
{
	char	*src;
	char	*tmp;

	src = ft_substr(input, pos[0], pos[1] - pos[0]);
	if (!src)
		return (-1);
	rf->redirect = token;
	if (ft_strchr(src, '*') && token != REDIRECT_LEFT_DOUBLE)
	{
		tmp = ft_strdup(src);
		expand_wildcard(&src);
		if (ft_strchr(src, REP_SPACE))
			rf->ambiguous = tmp;
		else
			free(tmp);
	}
	if (token == REDIRECT_LEFT_DOUBLE || token == REDIRECT_LEFT_SINGLE)
		rf->read = src;
	else
		rf->write = src;
	if (token == REDIRECT_LEFT_DOUBLE)
		heredoc_expansion(rf, input);
	truncate_character(src, REP_DQ);
	truncate_character(src, REP_SQ);
	return (0);
}

static void	add_file(t_cmd *command, char *src, int *pos, t_token token)
{
	t_file	*new;

	new = ft_calloc(1, sizeof(t_file));
	if (!new)
		handle_error(E_MALLOC, NULL, __func__);
	if (init_file(new, src, pos, token))
	{
		free(new);
		handle_error(E_MALLOC, NULL, __func__);
	}
	if (new->redirect == REDIRECT_LEFT_DOUBLE)
		add_file_to_list(&command->eof_rf, new);
	else
		add_file_to_list(&command->io_rf, new);
}

int	initialize_file_list(t_cmd *command, char *src, const char *redir[])
{
	int		i;
	int		idx;
	int		pos[2];
	t_token	token;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (src && src[i])
	{
		if (src[i] && (src[i] == REP_DQ || src[i] == REP_SQ))
			in_quotes = !in_quotes;
		else if (!in_quotes && find_string_match(&src[i], redir, &idx) == OK)
		{
			token = get_t_token(&src[i], ft_strlen(redir[idx]));
			get_redir_segment(&src[i], &pos[0], &pos[1], ft_strlen(redir[idx]));
			add_file(command, &src[i], pos, token);
			i += ft_strlen(redir[idx]);
			if (src[i] == '\0')
				break ;
			continue ;
		}
		i++;
	}
	return (0);
}

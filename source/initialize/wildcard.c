/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:59:42 by joralves          #+#    #+#             */
/*   Updated: 2025/02/21 12:46:08 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	identify_match_pattern(char *input, int *pos, int start_pos)
{
	int		i;
	int		j;
	int		in_quotes;

	i = start_pos;
	in_quotes = false;
	while (input[i])
	{
		if (input[i] == REP_DQ || input[i] == REP_SQ)
			in_quotes = !in_quotes;
		else if (!in_quotes && input[i] == '*')
		{
			j = i;
			while (j > 0 && input[j - 1] != REP_SPACE)
				j--;
			pos[0] = j;
			while (input[i] && input[i] != REP_SPACE)
				i++;
			pos[1] = i;
			return 1;	
		}
		i++;
	}
	return 0;
}

static void insert_wildcard(char **input_expanded, struct dirent *entry, int  *add_pos)
{
	char			*tmp;

	tmp = insert_string(*input_expanded, entry->d_name,  *add_pos);
	free(*input_expanded);
	if (!tmp)
		handle_error(E_MALLOC, NULL, __func__);
	*add_pos += ft_strlen(entry->d_name);
	*input_expanded = insert_string(tmp, "\003", *add_pos);
	free(tmp);
	if(!*input_expanded)
		handle_error(E_MALLOC, NULL, __func__);
	*add_pos += 1;
}

static void expand_wildcard_aux(char **input_expanded, char *pattern, int *pos, int pos_to_add)
{
	struct dirent 	*entry;
	DIR				*directory;
	
	directory = opendir(".");
	entry	=	readdir(directory);
	while (entry != NULL)
	{
		if (match_wildcard(pattern, entry->d_name))
			insert_wildcard(input_expanded, entry, &pos_to_add);
		entry = readdir(directory);
		if (!entry && pos_to_add !=  pos[1])
		{
			truncate_range(*input_expanded, pos[0], pos[1] - pos[0]);
			truncate_range(*input_expanded, ft_strlen(*input_expanded) -1, 1);
		}
	}
	closedir(directory);	
}


void	expand_wildcard(char **input_expanded)
{
	int				pos[2];
	int				start_pos;
	char 			*pattern;
	int				pos_to_add;
	
	start_pos = 0;
	while (identify_match_pattern(*input_expanded, pos, start_pos))
	{
		pos_to_add = pos[1];
		pattern = ft_substr(*input_expanded, pos[0], pos[1] - pos[0]);
		if (!pattern)
			handle_error(E_MALLOC, NULL, __func__);
		expand_wildcard_aux(input_expanded, pattern, pos, pos_to_add);
		start_pos = pos[1];		
		free(pattern);
	}
}

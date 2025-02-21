/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:59:42 by joralves          #+#    #+#             */
/*   Updated: 2025/02/21 12:15:21 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static bool is_pattern_done(const char *pattern, int p)
{

	while (pattern[p] == '*')
		p++;
	return (pattern[p] == '\0');
}

static int match_wd_aux(const char *pattern, const char *filename, int p, int f)
{	
	int sm_pos[2];

	ft_memset(sm_pos, -1, 8);
	while (filename[f])
	{
		if (pattern[p] == filename[f])
		{
			p++;
			f++;
		}
		else if (pattern[p] == '*')
		{
			sm_pos[0] = p++;
			sm_pos[1] = f;
		}
		else if (sm_pos[0] != -1)
		{
			p = sm_pos[0] + 1;
			f = ++sm_pos[1];
		}
		else
			return (0);
	}
	return (is_pattern_done(pattern, p));
}

int	match_wildcard(const char *pattern, const char *filename)
{
	int p;
	int f;

	p = 0;
	f = 0;
	if (match_wd_aux(pattern, filename, p, f))
		return 1;
	return 0;
}

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



static bool expand_wildcard_aux(char **input_expanded, char *pattern, int *pos)
{
	struct dirent *entry;
	DIR			*directory;
	int 		pos_to_add;
	bool		wild;
	
	directory = opendir(".");
	entry	=	readdir(directory);
	pos_to_add = pos[1];
	wild = false;
	while (entry != NULL)
	{
		if (match_wildcard(pattern, entry->d_name))
		{
			wild = true;
			*input_expanded = insert_string(*input_expanded, entry->d_name, pos_to_add);
			if (!input_expanded)
				handle_error(E_MALLOC, NULL, __func__);
			pos_to_add += ft_strlen(entry->d_name);
			printf("entry->d_name: %s\n", entry->d_name);
			printf("pos[0]: %d\n", pos[0]);
			printf("pos[1]: %d\n", pos[1]);
			printf("input_expanded_apos: %s\n", *input_expanded);
			*input_expanded = insert_string(*input_expanded, "\003", pos_to_add);
			pos_to_add += 1;
		}
		entry = readdir(directory);
		if (!entry && wild == true)
		{
			printf("FIZ AQUI\n");
			if (pos_to_add !=  pos[1])
			{
				truncate_range(*input_expanded, pos[0], pos[1] - pos[0]);
				truncate_range(*input_expanded, ft_strlen(*input_expanded) -1, 1);
			}
		}
	}
	closedir(directory);
	return (wild);
		
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
		pattern = ft_substr(*input_expanded, pos[0], pos[1] - pos[0]);
		if (!pattern)
			handle_error(E_MALLOC, NULL, __func__);
		expand_wildcard_aux(input_expanded, pattern, pos);
		start_pos = pos[1];
		if (*input_expanded[start_pos] == '\0')
			break;
		
	}
}

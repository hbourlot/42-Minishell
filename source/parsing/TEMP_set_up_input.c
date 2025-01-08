/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEMP_set_up_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:42:15 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/08 02:36:24 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_readline_node(t_shell *data, char *readline, const quotes, bool literal)
{
	int			i;
	t_readline	dummy;
	t_readline 	*last_node;
	t_readline	*to_allocate;
	char		*new_src;

	i = 0;
	last_node = get_last_node(data->readline_processed, get_offset(&dummy, &dummy.next));
	if (last_node)
		to_allocate = last_node->next;
	else
		to_allocate = last_node; // TODO: need to check if its really adding back properly;
	
	to_allocate = malloc(sizeof(t_readline));
	if (!to_allocate)
		return (-1);

	to_allocate->next = NULL;
	while (readline[i] != quotes)
		i++;
		
	new_src = ft_substr(readline, 0, i);
	if (!new_src)
		return (-1);
	if (literal)
		to_allocate->literal = new_src;
	else
		to_allocate->non_literal = new_src;
		
	readline += i; // TODO: Need to check if it's moving forward;
	return (0);
}

static int	handle_non_literal_string(t_shell *data, char *readline)
{
	int	i;
	
	i = 0;
	while (readline[i])
	{
		if (readline[i] == '\'')
		{
			if (initialize_readline_node(data, readline, '\'') < 0)
				return (-1);
			return (0);
		}
		else if (readline[i] == '"')
		{
			if (initialize_readline_node(data, readline, '"') < 0)
				return (-1);
			return (0);
		}
		i++;
	}
	if (initialize_new_input(data, readline, '\0') < 0)
		return (-1);
	return (0);
}

static int	handle_literal_string(t_shell *data, char *readline, const char quotes)
{
	int	i;

	i = 0;
	while (readline[i] != quotes)
		i++;
	// ? As long as when i call this function i know for sure all double quotes are even,
	// ? i dont need to check if there's still 
	if (initialize_readline_node(data, readline, quotes, true) < 0)
		return (-1);
	readline += 1;
	return (0);
}

int	initialize_input(t_shell *data, char *readline)
{
	bool	in_single_quotes;
	bool	in_double_quotes;
	int		i;
	
	i = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	skip_spaces(&readline);
	while (readline && readline[i])
	{
		if (readline[i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (readline[i] == '"')
			in_double_quotes = !in_double_quotes;
		else if (!in_single_quotes && !in_double_quotes 
			&& handle_non_literal_string(data, readline[i]))
				return (-1);
		else if (in_double_quotes && handle_literal_string(data, &readline[i], QUOTE_TYPE_DOUBLE))
				return (-1);
		else if (in_double_quotes && handle_literal_string(data, &readline[i], QUOTE_TYPE_DOUBLE))
				return (-1);
		i++;
	}
}

static void	set_new_character(char *readline, int single_quotes_occurrence, int double_quotes_occurrence)
{
	char	*temp;

	temp = readline;
	if (single_quotes_occurrence % 2 == 0)
	{
		while (temp)
		{
			temp = ft_strchr(temp, '\'');
			if (temp)
				temp[0] = QUOTE_TYPE_SINGLE;
		}
	}
	if (double_quotes_occurrence % 2 == 0)
	{
		while (temp)
		{
			temp = ft_strrchr(temp, '"');
			if (temp)
				temp[0] = QUOTE_TYPE_DOUBLE;
		}
	}
}

static void handle_non_paired_quotes(char *readline, int single_quotes_occurrence, int double_quotes_occurrence)
{
	char	*temp;
	char	*last_reference;
	
	temp = readline;
	if (single_quotes_occurrence % 2)
	{
		last_reference = ft_strrchr(readline, '\'');
		while (temp && temp != last_reference)
		{
			temp = ft_strchr(temp, '\'');
			if (temp)
				temp[0] = QUOTE_TYPE_SINGLE;
		}
	}
	if (double_quotes_occurrence % 2)
	{
		last_reference = ft_strrchr(readline, '"');
		while (temp && temp != last_reference)
		{
			temp = ft_strrchr(temp, '"');
			if (temp)
				temp[0] = QUOTE_TYPE_DOUBLE;
		}
	}
}

void	identify_and_replace_quotes(char *readline)
{
	int	i;
	int	single_quotes_occurrence;
	int	double_quotes_occurrence;

	
	i = -1;
	single_quotes_occurrence = 0;
	double_quotes_occurrence = 0;
	while (readline[++i])
	{
		if (readline[i] == '\'')
			single_quotes_occurrence += 1;
		if (readline[i] == '"')
			double_quotes_occurrence += 1;
	}
	set_new_character(readline, single_quotes_occurrence, double_quotes_occurrence); // ? Can be named handle_paired_quotes
	handle_non_paired_quotes(readline, single_quotes_occurrence, double_quotes_occurrence);
}

int	set_up_input(t_shell *data)
{
	identify_and_replace_quotes(data->readline);
	if (initialize_input(data, data->readline))
		return (-1);
	return (0);
}
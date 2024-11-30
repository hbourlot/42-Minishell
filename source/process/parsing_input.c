/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:27:32 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/30 17:05:14 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	find_matching_character(int *first, int *second, char *src, int character)
{
	int	i;

	i = 0;
	*first = -1;
	*second = -1;
	while (src[i])
	{
		if (src[i] == character && *first == -1)
			*first = src[i];		
		else if (src[i] == character && *second == -1)
			*second = src[i];
		i++;
	}
	if (*first != -1 && *second != -1)
		return (1);
	return (0);
}

int	count_char_occurrences(char *src, int character)
{
	int i;
	int nbr;

	nbr = 0;
	i = 0;
	if (!src || !*src)
		return (-1);
	while (src[i])
	{
		if (src[i] == character)
			nbr++;
		i++;
	}
	return (nbr);
}

int	parsing_input(char *input, t_cmd *command)
{
	int	start;
	int	end;
	char **input_splitted;

	start = 0;
	end = 0;
	while (*input)
	{
		if (char_cmp(*input, '|') && *(input + 1) && char_cmp(*input, '|'))
		{
			command->settings.or_next = true;
			command->pre_command = ft_substr(input, start, --end);
			start = end + 3;
		}
		else if (char_cmp(*input, '|'))
		{
			command->pre_command = ft_substr(input, start , --end);
			start = end + 2;
		}
		else if (*(input + 1) && !ft_strncmp(input, "&&", 2))
		{
			command->pre_command = ft_substr(input, start, --end);
			start = end + 3;
		}
		end++;
		*input++;
	}
}

char *find_first_occurrence(char *src, char **to_find)
{
	int		i;
	int		j;
	char 	*occurrence;
	char 	*first_occur;
	i = 0;
	
	occurrence = NULL;
	first_occur = NULL;
	while (src[i])
	{
		j = 0;
		while (to_find[j])
		{
			char *occurrence = ft_strstr(src + i, to_find[j]);
			if (!first_occur)
				first_occur = occurrence;
			if (occurrence && occurrence < first_occur)
				first_occur = occurrence;
		}
	}
	return (first_occur);
}



// int	parsing_input(char *input, t_cmd *cmd)
// {
// 	int		i;
// 	char	*sub;

// 	i = 0;
// 	sub = input;
// 	while (input[i])
// 	{
// 		sub = ft_strstr(sub, "||")
// 	}
// }

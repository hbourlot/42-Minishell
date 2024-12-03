/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:52 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/03 14:42:23 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int match_delimiter(char *input, const char *delimiters[], int first_match)
{
    int i = 0;
	if (first_match != -1)
	{
		while (*input && *input == ' ')
			input++;
	}
    while (delimiters[i])
    {
        if (!ft_strncmp(input, delimiters[i], ft_strlen(delimiters[i])))
            return i;
		i++;
    }
    return -1;
}

static bool is_delimiters_together(char *input, const char *delimiters[])
{
	int	first_match;
	int	second_match;

	first_match = -1;
    if (!input || !*input)
        return false;
    first_match = match_delimiter(input, delimiters, first_match);
    if (first_match != -1)
    {
        input += ft_strlen(delimiters[first_match]); 
        second_match = match_delimiter(input, delimiters, first_match);
        if (second_match != -1 && second_match != first_match)
            return true;
        return is_delimiters_together(input, delimiters);
    }
    return is_delimiters_together(input + 1, delimiters);
}


int	parsing_input(char *input, const char **delimiters)
{
	if (is_delimiters_together(input, delimiters))
	{
		printf("is_together\n");
		return (-1);
	}
	return (0);

}

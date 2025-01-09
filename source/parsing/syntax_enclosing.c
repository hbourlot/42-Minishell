/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_enclosing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:24:41 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/28 13:39:28 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	matching_enclosing(char *src, int *nbr_open, int *nbr_closed, const char tokens[])
{
	int	i;
	char	open;
	char	closed;
	
	*nbr_closed = 0;
	*nbr_open = 0;
	i = 0;
	if (!tokens || array_length((char **)tokens) != 2)
		return (-1);
	open = tokens[0];
	closed = tokens[1];
    while (src && *src)
    {
        if (*src == open)
            (*nbr_open)++;
        else if (*src == closed)
            (*nbr_closed)++;
        src++;
    }
	return (*nbr_open == *nbr_closed);
}


bool is_valid_enclosing_tokens(char *input)
{
	int			nbr_open;
	int			nbr_closed;
	const char 	parentheses[] = {'(', ')', '\0'};
	const char 	square_brackets[] = {'[', ']', '\0'};

    if (!matching_enclosing(input, &nbr_open, &nbr_closed, parentheses) || nbr_open != nbr_closed)
        return (false);
    if (!matching_enclosing(input, &nbr_open, &nbr_closed, square_brackets) || nbr_open != nbr_closed)
        return (false);
	
		
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:51:28 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 11:23:14 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_redirect_and_file(char **input, const char *redirects[], int *start, int *error)
{
    int 	end;
	int		idx;
	char	*to_remove;
	
	*error = 0;
    end = 0;
    to_remove = NULL;
    if (find_string_match(&(*input)[*start], redirects, &idx) == CMP_OK)
    {
        end = *start + ft_strlen(redirects[idx]);
        while ((*input)[end] && (*input)[end] == ' ')
            end++;
        while ((*input)[end] && (*input)[end] != ' ' && ft_strcmps(&(*input)[end], redirects) == ERROR)
            end++;
        to_remove = ft_substr(*input, *start, end - *start);
        if (!to_remove)
        {
            *error = ERROR;
            set_error(EXIT_FAILURE, "Malloc", NULL, __func__);
        }
    }
    return (to_remove);
}

int parsing_and_strip_redirects(char **input, const char *redirects[])
{
    int 	start;
    char 	*to_remove;
    char 	*new_input;
	int		error;

    if (!input || !*input)
        return (-1);
    start = 0;
    while ((*input)[start])
    {
        to_remove = extract_redirect_and_file(input, redirects, &start, &error);
		if (error == ERROR)
			return (ERROR);
        if (to_remove)
        {
            new_input = remove_substring(*(const char **)input, to_remove);
            if (!new_input)
                return (free(to_remove), ERROR);
            free_pointers(2, *input, to_remove);
            // free(to_remove);
            *input = new_input;
        }
        else
            start++;
    }
    return (EXIT_SUCCESS);
}

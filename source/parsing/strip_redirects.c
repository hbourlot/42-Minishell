/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:51:28 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/08 03:04:37 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_redirect_and_file(char **input, const char *redirects[],
		int *start, int *error)
{
	int		end;
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
		while ((*input)[end] && (*input)[end] != ' '
			&& ft_strcmps(&(*input)[end], redirects) == ERROR)
			end++;
		to_remove = ft_substr(*input, *start, end - *start);
		if (!to_remove)
		{
			*error = ERROR;
			set_error_parsing(1, "Malloc", NULL, __func__);
		}
	}
	return (to_remove);
}

/// @brief Parses and removes redirection operators and their files
///          from the input string.
/// @param input The user input string (modified in-place).
/// @param redirects Array of valid redirection operators.
/// @return EXIT_SUCCESS on success, or ERROR on failure.
int	strip_redirects(char **input, const char *redirects[])
{
	int		start;
	char	*to_remove;
	char	*new_input;
	int		error;

	if (!input)
		return (-1);
	if (!*input) // ? Pretty sure i can remove it since already came as NULL
		return (0);
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
			if (ft_strlen(new_input) == 0)
				return (free_pointers(3, input, &new_input, &to_remove), EXIT_SUCCESS);
			free_pointers(2, input, &to_remove);
			*input = new_input;
		}
		else
			start++;
	}
	if (all_same_char(*input, ' ') == true)
		free_pointers(1, input);
	return (EXIT_SUCCESS);
}


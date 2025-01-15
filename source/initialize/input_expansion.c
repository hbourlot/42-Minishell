/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:59:48 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/14 16:45:25 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_command_element(char *cmd_element)
{
	char	**cmd_tokens;
	int		i;
	char	*rest;

	rest = NULL;
	i = 0;
	cmd_tokens = tokenize_element(cmd_element);
	if (!cmd_tokens)
		return (free(cmd_element), NULL);
	while (cmd_tokens[i])
	{
		cmd_tokens[i] = process_variables(cmd_tokens[i]);
		rest = ft_append_and_free(rest, cmd_tokens[i]);
		if (!rest)
			return (free(cmd_element), free_split(cmd_tokens), NULL);
		free(cmd_tokens[i]);
		i++;
	}
	free(cmd_tokens);
	return (free(cmd_element), rest);
}

static char	**filter_non_empty(char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		if (*array[i])
		{
			array[j] = array[i];
			j++;
		}
		else
			free(array[i]);
		i++;
	}
	if (j == 0)
	{
		array[0] = ft_strdup("");
		if (!array[0])
			return (NULL);
		j++;
	}
	array[j] = NULL;
	return (array);
}

char	**process_command_input(char *input)
{
	char	**cmd_elements;
	int		i;

	i = 0;
	cmd_elements = ft_split(input, REP_SPACE);
	if (!cmd_elements)
		return (NULL);
	while (cmd_elements[i])
	{
		cmd_elements[i] = process_command_element(cmd_elements[i]);
		if (!cmd_elements[i])
			return (free_split(cmd_elements), NULL);
		i++;
	}
	cmd_elements = filter_non_empty(cmd_elements);
	if (!cmd_elements)
		return (free_split(cmd_elements), NULL);
	return (cmd_elements);
}

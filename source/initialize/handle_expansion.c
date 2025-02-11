/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:59:48 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 16:15:50 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_variable(t_cmd *command, char *var_name, bool double_quotes)
{
	char	*temp;
	char	*expanded_value;

	if (var_name[1] == '$')
		expanded_value = ft_itoa(getpid());
	else if (var_name[1] == '?')
		expanded_value = ft_itoa(get_shell()->exit_status);
	else
	{
		temp = hashmap_search(create_map(), var_name + 1);
		if (!temp)
			expanded_value = ft_strdup("");
		else if (double_quotes == false)
			expanded_value = ft_strtrim(temp, " ");
		else
			expanded_value = ft_strdup(temp);
	}
	if (!expanded_value)
		return (NULL);
	command->settings.expansion = true;
	return (expanded_value);
}

static char	*process_expansion(t_cmd *command, char *element, int i,
		bool double_quotes)
{
	int		j;
	char	*var_name;
	char	*expansion_value;
	char	*result;

	j = i + 1;
	if (element[j] == '$' || element[j] == '?')
		j++;
	else
		while (element[j] && (ft_isalnum(element[j]) || element[j] == '_'))
			j++;
	var_name = ft_substr(element, i, j - i);
	if (!var_name)
		return (NULL);
	expansion_value = expand_variable(command, var_name, double_quotes);
	free(var_name);
	if (!expansion_value)
		return (NULL);
	truncate_range(element, i, j - i);
	result = insert_string(element, expansion_value, i);
	if (!result)
		return (free(element), free(expansion_value), NULL);
	return (free(element), free(expansion_value), result);
}

static char	*handle_variable_expansion(t_cmd *command, char *element)
{
	int		i;
	bool	double_quotes;

	double_quotes = false;
	i = 0;
	if (element[0] == 1)
		return (element);
	if (element[0] == 2)
		double_quotes = true;
	while (element && element[i])
	{
		while (element[i] && element[i] != '$')
			i++;
		if (!element[i])
			break ;
		i++;
		if (element[i] == 1 || element[i] == 2 || element[i] == 3
			|| element[i] == ' ' || element[i] == '\0')
			continue ;
		element = process_expansion(command, element, i - 1, double_quotes);
		if (!element)
			return (NULL);
		i = 0;
	}
	return (element);
}

char	*handle_command_elements(t_cmd *command, char **elements)
{
	int		i;
	char	*result;

	result = NULL;
	i = 0;
	while (elements[i])
	{
		if (ft_strchr(elements[i], '$'))
		{
			elements[i] = handle_variable_expansion(command, elements[i]);
			if (!elements[i])
				return (free_split(elements), NULL);
		}
		result = ft_append_and_free(result, elements[i]);
		if (!result)
			return (free_split(elements), NULL);
		i++;
	}
	return (free_split(elements), result);
}

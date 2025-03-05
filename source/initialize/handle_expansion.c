/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:59:48 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/11 16:44:37 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_variable(bool *expanded, char *var_name, bool double_quotes)
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
	if (expanded)
		*expanded = true;
	return (expanded_value);
}

static char	*process_expansion(bool *expanded, char *element, int i,
		bool double_quotes)
{
	int		j;
	char	*var_name;
	char	*expansion_value;
	char	*result;

	j = i + 1;
	if (element[j] == '$' || element[j] == '?' || ft_isdigit(element[j]))
		j++;
	else
		while (element[j] && (ft_isalnum(element[j]) || element[j] == '_'))
			j++;
	var_name = ft_substr(element, i, j - i);
	if (!var_name)
		return (NULL);
	expansion_value = expand_variable(expanded, var_name, double_quotes);
	free(var_name);
	if (!expansion_value)
		return (NULL);
	truncate_range(element, i, j - i);
	result = insert_string(element, expansion_value, i);
	if (!result)
		return (free(element), free(expansion_value), NULL);
	return (free(element), free(expansion_value), result);
}

static char	*handle_variable_expansion(char *element, bool *expanded)
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
		if (!(element[i] == '$' || element[i] == '?')
			&& !(ft_isalnum(element[i]) || element[i] == '_'))
			continue ;
		element = process_expansion(expanded, element, i - 1, double_quotes);
		if (!element)
			return (NULL);
		i = 0;
	}
	return (element);
}

static void	filter_special_quotes(char *result)
{
	int		i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (result[i])
	{
		if (result[i] == REP_SQ || result[i] == REP_DQ)
			in_quotes = !in_quotes;
		else if (!in_quotes && result[i] == '$' && (result[i + 1] == REP_SQ
				|| result[i + 1] == REP_DQ))
		{
			truncate_range(result, i, 1);
			in_quotes = false;
			i = 0;
			continue ;
		}
		i++;
	}
}

char	*handle_command_elements(char **elements, bool *expanded)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (elements[i])
	{
		if (ft_strchr(elements[i], '$'))
		{
			elements[i] = handle_variable_expansion(elements[i], expanded);
			if (!elements[i])
				return (free_split(elements), NULL);
		}
		result = ft_append_and_free(result, elements[i]);
		if (!result)
			return (free_split(elements), NULL);
		i++;
	}
	filter_special_quotes(result);
	return (free_split(elements), result);
}

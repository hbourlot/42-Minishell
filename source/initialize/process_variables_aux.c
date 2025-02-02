/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:59:00 by joralves          #+#    #+#             */
/*   Updated: 2025/02/01 17:29:26 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_shell_variable(char *var_name)
{
	char	*temp;
	char	*expanded_value;

	if (var_name[1] == '$')
	{
		expanded_value = ft_itoa(getpid());
	}
	else if (var_name[1] == '?')
	{
		expanded_value = ft_itoa(get_shell()->exit_status);
	}
	else
	{
		temp = hashmap_search(create_map(), var_name + 1);
		expanded_value = ft_strtrim(temp, " ");
		free(temp);
	}
	free(var_name);
	if (!expanded_value)
		return (NULL);
	return (expanded_value);
}

static char	*expand_variables(char *str)
{
	char	**tokens;
	int		i;
	char	*result;

	tokens = tokenize_bash_variables(str);
	if (!tokens)
		return (free(str), NULL);
	result = NULL;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '$' && tokens[i][1] != '\0')
		{
			tokens[i] = expand_shell_variable(tokens[i]);
			if (!tokens[i])
				return (free_split(tokens), free(str), NULL);
		}
		result = ft_append_and_free(result, tokens[i]);
		if (!result)
			return (free_split(tokens), free(str), NULL);
		i++;
	}
	return (free_split(tokens), free(str), result);
}

static char	*remove_quotes(char *cmd_token)
{
	char	*result;
	size_t	len;

	len = ft_strlen(cmd_token);
	if (len == 2)
	{
		result = ft_strdup("");
		return (free(cmd_token), result);
	}
	result = ft_substr(cmd_token, 1, len - 2);
	free(cmd_token);
	if (!result)
		return (NULL);
	return (result);
}

char	*process_variables(char *cmd_token)
{
	if (cmd_token[0] == REP_SINGLE_QUOTE)
		return (remove_quotes(cmd_token));
	if (cmd_token[0] == REP_DOUBLE_QUOTE)
	{
		cmd_token = remove_quotes(cmd_token);
		if (!cmd_token)
			return (NULL);
	}
	if (ft_strchr(cmd_token, '$') == NULL)
		return (cmd_token);
	cmd_token = expand_variables(cmd_token);
	if (!cmd_token)
		return (NULL);
	return (cmd_token);
}

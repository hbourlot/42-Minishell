/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:59:00 by joralves          #+#    #+#             */
/*   Updated: 2025/01/14 16:02:06 by joralves         ###   ########.fr       */
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
		expanded_value = ft_itoa(get_shell()->last_exit_status);
	}
	else
	{
		temp = getenv(var_name + 1);
		expanded_value = ft_strtrim(temp, " ");
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

	result = ft_substr(cmd_token, 1, ft_strlen(cmd_token) - 2);
	free(cmd_token);
	if (!result)
		return (NULL);
	return (result);
}

static char	*process_cmd_parts(char **cmd_parts)
{
	int		i;
	char	*result;

	result = NULL;
	i = 0;
	while (cmd_parts[i])
	{
		if (ft_strchr(cmd_parts[i], '$'))
		{
			cmd_parts[i] = expand_variables(cmd_parts[i]);
			if (!cmd_parts[i])
				return (NULL);
		}
		result = ft_append_and_free(result, cmd_parts[i]);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

char	*process_variables(char *cmd_token)
{
	char	**cmd_parts;
	char	*result;

	result = NULL;
	if (cmd_token[0] == REP_SINGLE_QUOTE)
		return (remove_quotes(cmd_token));
	if (cmd_token[0] == REP_DOUBLE_QUOTE)
	{
		cmd_token = remove_quotes(cmd_token);
		if (!cmd_token)
			return (NULL);
	}
	cmd_parts = ft_split_keep_charset(cmd_token, " '/");
	if (!cmd_parts)
		return (free(cmd_token), NULL);
	result = process_cmd_parts(cmd_parts);
	if (!result)
		return (free_split(cmd_parts), free(cmd_token), NULL);
	return (free_split(cmd_parts), free(cmd_token), result);
}

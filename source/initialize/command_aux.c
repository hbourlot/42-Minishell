/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/08 14:58:01 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_command_to_list(t_cmd **command, t_cmd *new_command)
{
	t_cmd	*last;

	if (!(*command))
		*command = new_command;
	else
	{
		last = *command;
		while (last->next)
			last = last->next;
		last->next = new_command;
	}
	return (SUCCESS);
}

static int	initialize_command_struct(t_cmd **command, char *rl_splitted, t_token token_type)
{
	t_cmd	*new_command;

	new_command = ft_calloc(1, sizeof(t_cmd));
	if (!new_command)
		return (set_error_in(1, "\"Malloc\"", __func__, true), ERROR);
	new_command->input = ft_strdup(rl_splitted);
	if (!new_command->input)
		return (set_error_in(1, "\"Malloc\"", __func__, true), ERROR);
	new_command->delimiter = token_type;
	ft_memset(new_command->io, -1, 8);
	new_command->settings.is_safe_to_execve = true;
	new_command->next = NULL;
	if (ft_strlen(rl_splitted) == 0 || all_same_char(rl_splitted,
			REP_SPACE))
		new_command->settings.only_tokens = true;
	return (add_command_to_list(command, new_command));
}

static int	handle_file_tokens(t_shell *data, t_cmd *command)
{
	const char	*file_tokens[] = {">>", ">", "<", NULL};

	(void)data;
	if (initialize_file_list(command->input, file_tokens,
			&command->redir_files))
	{
		set_error_in(1, "\"File Redirection\"", __func__, true);
		return (-1);
	}
	strip_redirects(command->input, file_tokens);
	if (ft_strlen(command->input) == 0 || all_same_char(command->input,
			REP_SPACE))
	{
		command->settings.is_safe_to_execve = false;
	}
	return (0);
}

static int	prepare_execve_parameters(t_cmd *command, t_shell *data)
{
	command->envp = data->envp;
	command->args = process_command_input(command);
	if (!command->args && command->settings.expansion == false)
	{
		set_error_in(1, "Malloc", __func__, true);
		return (handle_error());
	}
	debug_command_args(data);
	command->path = get_path(command->args[0], data->env_paths);
	if (!command->path && command->settings.expansion == false)
		return (set_error_in(1, "\"Path\"", __func__, true), ERROR);
	if (command->settings.expansion == true && !command->args)
		command->settings.is_safe_to_execve = false;
	return (SUCCESS);
}

int	add_command(t_cmd **command, char *rl_splitted, t_shell *data,
		t_token token_type)
{
	t_cmd	dummy;
	t_cmd	*last_node;

	replace_characters(rl_splitted, REP_AND, '&');
	replace_characters(rl_splitted, REP_PIPE, '|');
	if (initialize_command_struct(command, rl_splitted, token_type) < 0)
		return (ERROR);
	last_node = get_last_node(data->command, get_offset(&dummy, &dummy.next));
	// expand here
	
	if (handle_file_tokens(data, last_node) < 0)
		return (ERROR);
	if (last_node->settings.is_safe_to_execve == true)
	{
		if (prepare_execve_parameters(last_node, data) < 0)
			return (ERROR);
		set_builtin_flag(last_node);
	}
	return (SUCCESS);
}

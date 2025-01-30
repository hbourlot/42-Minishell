/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/29 01:11:41 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	initialize_command_struct(t_cmd **command, char *readline_splitted,
		t_token token_type)
{
	t_cmd	*new_command;
	t_cmd	*last;

	new_command = ft_calloc(1, sizeof(t_cmd));
	if (!new_command)
		return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
	new_command->input = ft_strdup(readline_splitted);
	if (!new_command->input)
		return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
	new_command->delimiter = token_type;
	new_command->fd_in = -1;
	new_command->fd_out = -1;
	new_command->next = NULL;
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

static int	handle_file_tokens(t_shell *data, t_cmd *command,
		char *readline_splitted)
// Todo: Prob i can remove the readline_splitted parameter here
{
	const char *file_tokens[] = {">", ">>", "<", NULL};
	sort_strings_by_length_desc(file_tokens);
	if (initialize_file_list(command->input, file_tokens,
			&command->redir_files) < 0)
	{
		set_error_initialize(1, "\"File Redirection\"", __func__, true);
		return (ERROR);
	}
	strip_redirects(command->input, file_tokens);
	if (ft_strlen(command->input) == 0 || all_same_char(command->input, ' '))
		// ? which means might only be files to open or here_doc
		command->settings.only_tokens = true;
	return (0);
}

static int	prepare_execve_parameters(t_cmd *command, t_shell *data)
{
	command->envp = data->envp;
	identify_and_replace_sq_tokens(&command->input);
	command->args = process_command_input(command->input);
	if (!command->args)
	{
		set_error_initialize(1, "Malloc", __func__, true);
		return (handle_error());
	}
	command->path = get_path(command->args[0], data->env_paths);
	if (!command->path || !command->args)
		return (set_error_initialize(1, "\"Path\"", __func__, true), ERROR);
	return (SUCCESS);
}

int	add_command(t_cmd **command, char *readline_splitted, t_shell *data,
		t_token token_type)
{
	t_cmd	dummy;
	t_cmd	*last_node;

	if (initialize_command_struct(command, readline_splitted, token_type) < 0)
		return (ERROR);
	last_node = get_last_node(data->command, get_offset(&dummy, &dummy.next));
	if (handle_file_tokens(data, last_node, readline_splitted) < 0)
		return (ERROR);
	if ((*command)->settings.only_tokens == false)
	{
		if (prepare_execve_parameters(last_node, data) < 0)
			return (ERROR);
	}
	// !!!!!!!!! Flag built in
	set_builtin_flag(last_node);
	//* To remove, just testing builtins
	process_builtin(data, last_node);
	//* ↑↑↑↑↑↑↑↑↑↑↑
	return (SUCCESS);
}

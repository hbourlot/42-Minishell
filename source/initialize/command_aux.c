/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/04 21:04:38 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_command_to_list(t_cmd **command, t_cmd *new_command)
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
}

static void	initialize_command_struct(t_cmd **command, char *rl_splitted,
		t_token id)
{
	t_cmd	*new_command;

	new_command = ft_calloc(1, sizeof(t_cmd));
	if (!new_command)
		handle_error(E_MALLOC, NULL, __func__);
	new_command->input = ft_strdup(rl_splitted);
	if (!new_command->input)
	{
		free_pointers(1, &new_command);
		handle_error(E_MALLOC, NULL, __func__);
	}
	new_command->delimiter = id;
	ft_memset(new_command->io, -1, 8);
	new_command->fd_eof = -1;
	new_command->settings.iste = true;
	new_command->next = NULL;
	add_command_to_list(command, new_command);
}

static void	handle_file_tokens(t_cmd *command, bool here_doc)
{
	const char	*file_tokens[] = {">>", ">", "<", NULL};
	const char	*file_doc[] = {"<<", NULL};
	char		*input;

	if (here_doc)
	{
		input = command->input;
		if (initialize_file_list(command, command->input, file_doc))
			handle_error(E_MALLOC, NULL, __func__);
		strip_redirects(command->input, file_doc);
	}
	else
	{
		input = command->input_expanded;
		if (initialize_file_list(command, command->input_expanded, file_tokens))
			handle_error(E_MALLOC, NULL, __func__);
		strip_redirects(command->input_expanded, file_tokens);
	}
	if ((ft_strlen(input) == 0 || all_same_char(input, REP_SPACE))
		&& command->settings.expansion == false)
		command->settings.iste = false;
}

void	prepare_parameters(t_cmd *command, t_shell *data)
{
	handle_file_tokens(command, true);
	command->input_expanded = expand_command_input(command->input,
			&command->settings.expansion);
	handle_file_tokens(command, false);
	expand_wildcard(&command->input_expanded);
	if (command->settings.iste == false)
		return ;
	command->args = process_command_input_expanded(command);
	command->path = get_path(command->args[0], data->env_paths);
	if (!command->path && command->settings.expansion == false)
		handle_error(E_MALLOC, NULL, __func__);
	if (command->settings.expansion == true && !command->args)
		command->settings.iste = false;
	set_builtin_flag(command);
}

void	add_command(t_cmd **command, char *rl_splitted, t_shell *data,
		t_token id)
{
	t_cmd	dummy;
	t_cmd	*last_node;

	replace_characters(rl_splitted, REP_AND, '&');
	replace_characters(rl_splitted, REP_PIPE, '|');
	initialize_command_struct(command, rl_splitted, id);
	last_node = get_last_node(data->command, get_offset(&dummy, &dummy.next));
	prepare_parameters(last_node, data);
}

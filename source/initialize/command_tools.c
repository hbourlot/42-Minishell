/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/13 16:40:55 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	initialize_command_struct(t_cmd **command, char *input_splitted)
{
	*command = ft_calloc(1, sizeof(t_cmd));
	if (!*command)
		return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
	(*command)->input = ft_strdup(input_splitted);
	if (!(*command)->input)
		return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
	(*command)->fd_in = -1;
	(*command)->fd_out = -1;
	return (SUCCESS);
}

// Todo: Prob i can remove the input_splitted parameter here
static int	handle_redirection(t_cmd *command, char *input_splitted)
{
	const char	*file_redirects[] = {">", ">>", "<", NULL};
	const char	*here_doc_redirects[] = {"<<", NULL};

	if (initialize_here_doc(command->input, &command->settings.eof) < 0
		|| strip_redirects(&command->input, here_doc_redirects) < 0)
	{
		set_error_initialize(1, "\"EOF Redirection\"", __func__, true);
		return (ERROR);
	}
	if (initialize_file_list(command->input, file_redirects,
			&command->redir_files) < 0 || strip_redirects(&command->input,
			file_redirects) < 0)
	{
		set_error_initialize(1, "\"File Redirection\"", __func__, true);
		return (ERROR);
	}
	if (!command->input)
		// ? which means might only be files to open or here_doc
		command->settings.only_tokens = true;
	return (SUCCESS);
}



static int	prepare_execve_parameters(t_cmd *command, t_shell *data)
{
	command->envp = data->envp;
	identify_and_replace_sq_tokens(&command->input);
	command->args = process_command_input(command->input);

// ! NEED TO URGENT
	if (command->args && !*command->args[0])
	{
		command->path = NULL;
		return (set_error_initialize(1, NULL, __func__, false), 2);
	}
	command->path = get_path(command->args[0], data->env_paths);
	if (!command->path || !command->args)
		return (set_error_initialize(1, "\"Path/Args\"", __func__, true),
			ERROR);
	return (SUCCESS);
}

int	add_command(t_cmd **command, char *input_splitted, t_shell *data)
{
	if (initialize_command_struct(command, input_splitted) < 0)
		return (ERROR);
	if (handle_redirection(*command, input_splitted) < 0)
		return (ERROR);
	if ((*command)->settings.only_tokens == false
		&& prepare_execve_parameters(*command, data) < 0)
		return (ERROR);
	return (SUCCESS);
}

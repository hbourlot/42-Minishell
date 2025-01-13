/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/13 17:19:42 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int initialize_command_struct(t_cmd **command, char *readline_splitted)
{
    if (!readline_splitted)
        return 0;
    *command = ft_calloc(1, sizeof(t_cmd));
    if (!*command)
        return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
    (*command)->input = ft_strdup(readline_splitted);
    if (!(*command)->input)
        return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
    (*command)->fd_in = -1;
    (*command)->fd_out = -1;
    return (SUCCESS);
}

static int handle_file_tokens(t_shell *data, t_cmd *command, char *readline_splitted) // Todo: Prob i can remove the readline_splitted parameter here
{
    const char  *file_tokens[] = {">", ">>", "<", NULL};

    if (initialize_file_list(command->input, file_tokens, &command->redir_files) < 0 ||
        strip_redirects(&command->input, file_tokens) < 0)
    {
        set_error_initialize(1, "\"File Redirection\"", __func__, true);
        return (ERROR);
    }
    if (!command->input) // ? which means might only be files to open or here_doc
        command->settings.only_tokens = true;
    return (0);
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

int add_command(t_cmd **command, char *readline_splitted, t_shell *data)
{
    if (initialize_command_struct(command, readline_splitted) < 0)
        return (ERROR);
    if (handle_file_tokens(data, *command, readline_splitted) < 0)
        return (ERROR);
    if ((*command)->settings.only_tokens == false && 
        prepare_execve_parameters(*command, data) < 0)
        return (ERROR);
    return (SUCCESS);
}

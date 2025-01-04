/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/02 17:12:26 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int initialize_command_struct(t_cmd **command, char *input_splitted)
{
    *command = ft_calloc(1, sizeof(t_cmd));
    if (!*command)
        return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
    (*command)->input = ft_strdup(input_splitted);
    if (!(*command)->input)
        return (set_error_initialize(1, "\"Malloc\"", __func__, true), ERROR);
    (*command)->in_fd = -1;
    (*command)->out_fd = -1;
    return (SUCCESS);
}
    
static int handle_redirection(t_cmd *command, char *input_splitted) // Todo: Prob i can remove the input_splitted parameter here
{
    const char  *file_redirects[] = {">", ">>", "<", NULL};
    const char  *here_doc_redirects[] = {"<<", NULL};

    if (initialize_here_doc(command->input, &command->settings.eof) < 0 ||
        strip_redirects(&command->input, here_doc_redirects) < 0)
    {
        set_error_initialize(1, "\"EOF Redirection\"", __func__, true);
        return (ERROR);
    }

    if (initialize_file_list(command->input, file_redirects, &command->redir_files) < 0 ||
        strip_redirects(&command->input, file_redirects) < 0)
    {
        set_error_initialize(1, "\"File Redirection\"", __func__, true);
        return (ERROR);
    }
    if (!command->input) // ? which means might only be files to open or here_doc
        command->settings.only_tokens = true;
    return (SUCCESS);
}

static int set_command_path_and_args(t_cmd *command, t_shell *data)
{
    command->envp = data->envp;
    command->path = get_path(command->input, data->env_paths);
    command->args = get_command_args(command->input);
    if (!command->path || !command->args)
        return (set_error_initialize(1, "\"Path/Args\"", __func__, true), ERROR);
    return (SUCCESS);
}

int add_command(t_cmd **command, char *input_splitted, t_shell *data)
{
    if (initialize_command_struct(command, input_splitted) < 0)
        return (ERROR);
    if (handle_redirection(*command, input_splitted) < 0)
        return (ERROR);
    if ((*command)->settings.only_tokens == false && 
        set_command_path_and_args(*command, data) < 0)
        return (ERROR);
    return (SUCCESS);
}

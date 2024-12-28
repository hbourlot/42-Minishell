/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/28 18:19:04 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int init_command_struct(t_cmd **command, char *input_splitted)
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

static int handle_redirection(t_cmd *command, char *input, const char *redirects[])
{
    if (init_file_list(input, redirects, &command->redir_files) < 0 ||
        parsing_and_strip_redirects(&command->input, redirects) < 0)
        return (set_error_initialize(1, "\"Redirection\"", __func__, true), ERROR);
    if (command->redir_files && ft_strlen(command->input) == 0) // Commands like "> file"
        command->settings.only_redir_files = true;
    
    return (SUCCESS);
}

static int set_command_path_and_args(t_cmd *command, t_shell *data)
{
    const char *alternative_args[] = {"", "", NULL};

    command->envp = data->envp;
    command->path = get_path(command->input, data->env_paths);
    command->args = get_command_args(command->input);
    if (!command->path || !command->args)
    {
        if (!command->path)
            printf("NOT PATH\n");
        if (!command->args)
            printf("NOT ARGS\n");
        return (set_error_initialize(1, "\"Path/Args\"", __func__, true), ERROR);
    }
    return (SUCCESS);
}

int add_command(t_cmd **command, char *input_splitted, t_shell *data, const char *redirects[])
{
    if (init_command_struct(command, input_splitted) < 0)
        return (ERROR);
    if (handle_redirection(*command, input_splitted, redirects) < 0)
        return (ERROR);
    if ((*command)->settings.only_redir_files == false)
    {
        if (set_command_path_and_args(*command, data) < 0)
            return (ERROR);
    }
    return (SUCCESS);
}

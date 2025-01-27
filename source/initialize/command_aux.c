/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:40:08 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/27 16:12:19 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int initialize_command_struct(t_cmd **command, char *readline_splitted, t_token token_type)
{
    t_cmd *new_command;
    t_cmd *last;
    
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
    if (ft_strlen(readline_splitted) == 0 || all_same_char(readline_splitted, REP_SPACE))
        new_command->settings.only_tokens = true;
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

static int handle_file_tokens(t_shell *data, t_cmd *command, char *readline_splitted) // Todo: Prob i can remove the readline_splitted parameter here
{
    const char  *file_tokens[] = {">>", ">", "<", NULL};

    if (initialize_file_list(command->input, file_tokens, &command->redir_files))
    {
        set_error_initialize(1, "\"File Redirection\"", __func__, true);
        return (-1);
    }
    strip_redirects(command->input, file_tokens);
    if (ft_strlen(command->input) == 0 || all_same_char(command->input, REP_SPACE))
        command->settings.only_tokens = true;
    return (0);
}

static int	prepare_execve_parameters(t_cmd *command, t_shell *data)
{
	command->envp = data->envp;
    
	command->args = process_command_input(command->input);
    if (!command->args)
    {
        set_error_initialize(1, "Malloc", __func__, true);
        return (handle_error());
    }
	command->path = get_path(command->args[0], data->env_paths);
	if (!command->path || !command->args)
		return (set_error_initialize(1, "\"Path\"", __func__, true),
			ERROR);
	return (SUCCESS);
}

void    replace_special_chars_in_literals(char *readline_splitted)
{
        replace_characters(readline_splitted, REP_AND, '&');
        replace_characters(readline_splitted, REP_PIPE, '|');   
}


int add_command(t_cmd **command, char *readline_splitted, t_shell *data, t_token token_type)
{
    t_cmd   dummy;
    t_cmd   *last_node;
    
    replace_special_chars_in_literals(readline_splitted);
    if (initialize_command_struct(command, readline_splitted, token_type) < 0)
        return (ERROR);
    last_node = get_last_node(data->command, get_offset(&dummy, &dummy.next));

    if (handle_file_tokens(data, last_node, readline_splitted) < 0)
        return (ERROR);
    
    if (last_node->settings.only_tokens == false)
    {
        if (prepare_execve_parameters(last_node, data) < 0)
            return (ERROR);
    }    
    return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 12:28:21 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int  add_command(t_cmd **command, char *input_splitted, t_shell *data, const char *redirects[])
{
    *command = ft_calloc(1, sizeof(t_cmd));
    if (!*command)
        return (set_error(1, "\"Malloc\"", NULL, __func__), ERROR);
    (*command)->input = ft_strdup(input_splitted);
    if (!(*command)->input)
        return (set_error(1, "\"Malloc\"", NULL, __func__), ERROR);
    if (init_file_list(input_splitted, redirects, &(*command)->file_list) < 0 ||
         parsing_and_strip_redirects(&(*command)->input, redirects) < 0)
        return (set_error(1, "\"Malloc\"", NULL, __func__), ERROR);
    (*command)->envp = data->envp;
    (*command)->path = get_path((*command)->input, data->env_paths);
    (*command)->args = get_command_args((*command)->input);
    if (!(*command)->path || !(*command)->args)
        return (set_error(1, "\"Malloc\"", NULL, __func__), ERROR);
    (*command)->in_fd = -1;
    (*command)->out_fd = -1;
    return (SUCCESS);
}

static int parsing_command_input(t_shell *data, char *input, const char *delimiters[])
{
    int i;

    i = 0;
    data->input_splitted = split_by_multiple_tokens(input, delimiters);
    if (!data->input_splitted)
        return (ERROR);
    return (SUCCESS);
}

static int create_command_list(t_shell *data, const char *redirects[])
{
    t_cmd   *current;
    int     i;

	i = 0;
    if (add_command(&data->command, data->input_splitted[i++], data, redirects) < 0)
        return (ERROR);
    current = data->command;
    while (data->input_splitted[i])
    {   
        if (add_command(&current->next, data->input_splitted[i++], data, redirects) < 0)
            return (ERROR);
        current = current->next;
    }
	data->nbr_of_commands = i;
    return (SUCCESS);
}

int init_command(char *input)
{
    const char  *redirects[] = {">", ">>", "<", "<<", NULL};
	const char  *delimiters[] = {"|", "||", "&&", "&", NULL};
    t_shell     *data;

	data = get_shell();
    if (parsing_command_input(data, input, delimiters) < 0 ||
         create_command_list(data, redirects) < 0)
        return (ERROR);
    // cleanup_shell(data);
    // debug_command_file_list(get_shell());
    // debug_input_splitted(data);
    // free(input);
    // cleanup_shell(data);
    // exit(EXIT_SUCCESS);
    // if (set_redirect(data->command))
    return (SUCCESS);
}

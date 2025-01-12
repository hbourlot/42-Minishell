/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/12 14:31:35 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int split_command_input(t_shell *data, char *input, const char *delimiters[])
{
    int i;

    i = 0;
    data->readline_splitted = split_by_multiple_tokens(input, delimiters);
    if (!data->readline_splitted)
        return (ERROR);
    return (SUCCESS);
}

static int create_command_list(t_shell *data)
{
    t_cmd   *current; 
    int     i;

	i = 0;
    if (add_command(&data->command, data->readline_splitted[i++], data) < 0)
        return (ERROR);
    current = data->command;
    while (data->readline_splitted[i])
    {   
        if (add_command(&current->next, data->readline_splitted[i++], data) < 0)
            return (ERROR);
        current = current->next;
    }
	data->nbr_of_commands = i;
    return (SUCCESS);
}

static bool there_no_more_command(t_shell *data)
{
    const char *to_compare[] = {"<<", ">>", "<", ">", "||", "|", "&&", " ", NULL};
    int i;

    i = 0;
    sort_strings_by_length_desc((char **)to_compare);
    while (data->readline && data->readline[i])
    {
        if (ft_strcmps(&data->readline[i], to_compare) == -1)
            return (false);
        i++;
    }
    return (true);
}

static int handle_eof(t_shell *data)
{
    int i;
    const char *eof_token[] = {"<<", NULL};

    i = 0;
    if (initialize_eof(data->readline, &data->eof) < 0)
    {
        set_error_initialize(1, "\"EOF Redirection\"", __func__, true);
        return -1;
    }
    if (strip_redirects(&data->readline, eof_token) < 0)
    {
        set_error_initialize(1, "\"Strip redirects\"", __func__, true);
        return -1;
    }
    if (there_no_more_command(data))
        free_pointers(1, &data->readline);
    return (0);
}

int init_command(char *input)
{
	const char  *delimiters[] = {"|", "||", "&&", "&", NULL};
    t_shell     *data;

	data = get_shell();
    if (handle_eof(data))
        return -1;
    if (data->readline && (split_command_input(data, data->readline, delimiters) < 0 ||
        create_command_list(data) < 0))
            return -1;
    return (SUCCESS);
}

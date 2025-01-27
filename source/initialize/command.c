/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/27 16:02:05 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int split_command_input(t_shell *data, const char *delimiters[])
{
    int i;

    i = 0;
    sort_strings_by_length_desc((char **)delimiters);
    data->readline_splitted = split_by_multiple_tokens(data->readline, delimiters);
    if (!data->readline_splitted)
        return (ERROR);
    // replace_characters(data->readline, REP_PIPE, '|');
    // replace_characters(data->readline, REP_AND, '&');
    return (SUCCESS);
}

static int create_command_list(t_shell *data, const char *delimiters[])
{
    t_token token_type;
    int     i;
    int     idx;
    char    *src;

    i = 0;
    src = data->readline;
    while (data->readline_splitted[i])
    {
        src = ft_strstr_any(src, delimiters);
        if (find_string_match(src, delimiters, &idx) == CMP_OK)
        {
            token_type = get_t_token((char *)delimiters[idx], ft_strlen(delimiters[idx]));
            src += ft_strlen(delimiters[idx]);
            if (add_command(&data->command, data->readline_splitted[i++], data, token_type) < 0)
                return (ERROR);
        }
        else
        {
            if (add_command(&data->command, data->readline_splitted[i++], data, PIPE_SINGLE) < 0)
                return (ERROR);
        }
    }
    data->nbr_of_commands = i;
    return (SUCCESS);
}

static int handle_eof(t_shell *data)
{
    int i;
    const char *eof_token[] = {"<<", NULL};
    const char  *delimiters_tokens[] = {"||", "|", NULL};

    i = 0;
    if (initialize_eof(data->readline, &data->eof) < 0)
    {
        set_error_initialize(1, "\"EOF_HERE_DOC\"", __func__, true);
        return -1;
    }
    strip_redirects(data->readline, eof_token);
    if (ft_strlen(data->readline) == 0 || all_same_char(data->readline, REP_SPACE))
        free_pointers(1, &data->readline);
    return (0);
}

int init_command(t_shell *data)
{
	const char  *delimiters[] = {"||", "|", "&&", NULL};

    if (handle_eof(data))
        return -1;
    if (data->readline && (split_command_input(data, delimiters) < 0 ||
        create_command_list(data, delimiters) < 0))
            return -1;  
    return (SUCCESS);
}

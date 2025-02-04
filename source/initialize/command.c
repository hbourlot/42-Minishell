/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 22:38:24 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int split_command_input(t_shell *data, const char *delimiters[])
{
    sort_strings_by_length_desc((char **)delimiters);
    data->readline_splitted = split_by_multiple_tokens(data->readline, delimiters);
    if (!data->readline_splitted)
        return (ERROR);
    return (SUCCESS);
}

// static int create_command_list(t_shell *data, const char *delimiters[])
// {
//     t_token token_type;
//     int     i;
//     int     idx;
//     char    *src;

//     i = 0;
//     src = data->readline;
//     while (data->readline_splitted[i])
//     {
//         src = ft_strstr_any(src, delimiters);
//         if (find_string_match(src, delimiters, &idx) == CMP_OK)
//         {
//             token_type = get_t_token((char *)delimiters[idx], ft_strlen(delimiters[idx]));
//             src += ft_strlen(delimiters[idx]);
//             if (add_command(&data->command, data->readline_splitted[i++], data, token_type) < 0)
//                 return (ERROR);
//         }
//         else
//         {
//             if (add_command(&data->command, data->readline_splitted[i++], data, PIPE_SINGLE) < 0)
//                 return (ERROR);
//         }
//     }
//     data->nbr_of_commands = i;
//     return (SUCCESS);
// }

static int create_command_list(t_shell *data, const char *delimiters[])
{
    t_token token_type;
    int     i;
    int     idx;
    char    *src;
    int     match_result;

    i = 0;
    src = data->readline;
    while (data->readline_splitted[i])
    {
        src = ft_strstr_any(src, delimiters);
        match_result = find_string_match(src, delimiters, &idx);
        if (match_result == CMP_OK)
        {
            token_type = get_t_token((char *)delimiters[idx], ft_strlen(delimiters[idx]));
            src += ft_strlen(delimiters[idx]);
        }
        else
            token_type = NO_TOKEN;
        if (add_command(&data->command, data->readline_splitted[i++], data, token_type) < 0)
            return (ERROR);
    }
    data->nbr_of_commands = i;
    return (SUCCESS);
}

static int handle_eof(t_shell *data)
{
    const char *eof_token[] = {"<<", NULL};
    // const char  *delimiters_tokens[] = {"||", "|", NULL};

    
    if (initialize_eof(data->readline, &data->eof) < 0)
    {
        set_error_in(1, "\"EOF_HERE_DOC\"", __func__, true);
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
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/29 13:34:24 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int split_command_input(t_shell *data, char *input, const char *delimiters[])
{
    int i;

    i = 0;
    data->input_splitted = split_by_multiple_tokens(input, delimiters);
    if (!data->input_splitted)
        return (ERROR);
    return (SUCCESS);
}

static int create_command_list(t_shell *data)
{
    t_cmd   *current;
    int     i;

	i = 0;
    if (add_command(&data->command, data->input_splitted[i++], data) < 0)
        return (ERROR);
    current = data->command;
    while (data->input_splitted[i])
    {   
        if (add_command(&current->next, data->input_splitted[i++], data) < 0)
            return (ERROR);
        current = current->next;
    }
	data->nbr_of_commands = i;
    return (SUCCESS);
}

int init_command(char *input)
{
    // const char  *redirects[] = {">", ">>", "<", "<<", NULL};
	const char  *delimiters[] = {"|", "||", "&&", "&", NULL};
    t_shell     *data;

	data = get_shell();
    if (split_command_input(data, input, delimiters) < 0 ||
         create_command_list(data) < 0)
        return (ERROR);
    return (SUCCESS);
}

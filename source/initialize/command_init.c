/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:56:28 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/29 15:31:22 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/// @brief Initializes the linked list of commands with input strings and other default values.
/// @param input_splitted An array of strings representing commands or arguments.
/// @param command A pointer to the head of the linked list of commands.
/// @return 0 on success, -1 if the input is invalid.
int initialize_command(char **input_splitted, t_cmd *command)
{
    int     i;
    
    i = 0;
    if (!input_splitted || !*input_splitted)
        return (-1);
    while (command)
    {
        // token_init(input_splitted[i], &command->token);
        command->pre_command = input_splitted[i];
        command->args = get_command_args(input_splitted[i]);
        command = command->next;
        i++;
    }
    return (0);
}

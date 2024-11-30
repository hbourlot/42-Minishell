/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:56:28 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/30 17:03:08 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/// @brief Initializes the linked list of commands with input strings and other default values.
/// @param input_splitted An array of strings representing commands or arguments.
/// @param command A pointer to the head of the linked list of commands.
/// @return 0 on success, -1 if the input is invalid.
// int initialize_command(char **input_splitted, t_cmd *command)
int initialize_command(char *input, t_cmd *command)
{
	int	i;
	char **input_splitted;

	if (!input || !*input)
        return (-1);
    input_splitted = ft_split(input, '|');
	if (!input_splitted)
		return (-1); //! Error managing here
	i = 0;
	while (*input)
	{
		if (char_cmp(*input, '|') && *(input + 1) && char_cmp(*input, '|'))
			command->settings.or_next = true;
		if (char_cmp(*input, '|'))
			command->pre_command = input_splitted[i++];
		input++;
	}
    return (0);
}

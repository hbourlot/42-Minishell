/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_expanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:15:08 by joralves          #+#    #+#             */
/*   Updated: 2025/02/11 21:07:40 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_command_input_expanded(t_cmd *command)
{
	char	**cmd_args;
	int		i;

	i = 0;
	identify_and_replace_sqpa_tokens(command->input_expanded);
	replace_characters(command->input_expanded, REP_PIPE, '|');
	replace_characters(command->input_expanded, REP_AND, '&');
	cmd_args = ft_split(command->input_expanded, REP_SPACE);
	if (!cmd_args && command->settings.expansion == false)
		handle_error(E_MALLOC, NULL, __func__);
	while (cmd_args[i])
	{
		truncate_character(cmd_args[i], 1);
		truncate_character(cmd_args[i], 2);
		i++;
	}
	return (cmd_args);
}

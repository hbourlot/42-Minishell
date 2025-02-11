/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_expanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:15:08 by joralves          #+#    #+#             */
/*   Updated: 2025/02/11 14:27:35 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**process_command_input_expanded(t_cmd *command)
{
	char	**cmd_args;

	identify_and_replace_sqpa_tokens(command->input_expanded);
	replace_characters(command->input_expanded, REP_PIPE, '|');
	replace_characters(command->input_expanded, REP_AND, '&');
	if (ft_strchr(command->input_expanded, REP_DQ)
		|| ft_strchr(command->input_expanded, REP_SQ))
	{
		truncate_character(command->input_expanded, 2);
		truncate_character(command->input_expanded, 1);
	}
	cmd_args = ft_split(command->input_expanded, REP_SPACE);
	if (!cmd_args && command->settings.expansion == false)
		handle_error(E_MALLOC, NULL, __func__);
	return (cmd_args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_expanded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:15:08 by joralves          #+#    #+#             */
/*   Updated: 2025/02/11 18:32:38 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	iter_special_replace(t_cmd *command)
{
	int 	i;
	char 	*ptr;

	i = 0;
	while (command->input_expanded[i] && command->input_expanded[i] == REP_SPACE)
		i++;
	if (command->input_expanded[i] == REP_SQ || command->input_expanded[i] == REP_DQ)
	{
		ptr = ft_strchr(command->input_expanded, REP_DQ);
		if (ptr && ptr[1] != REP_DQ)
			truncate_character(command->input_expanded, 2);
		ptr = ft_strchr(command->input_expanded, REP_SQ);
		if (ptr && ptr[1] != REP_SQ)
			truncate_character(command->input_expanded, 1);
		return;
	}
}


char	**process_command_input_expanded(t_cmd *command)
{
	char	**cmd_args;
	char	*ptr;

	(void)ptr;
	identify_and_replace_sqpa_tokens(command->input_expanded);
	replace_characters(command->input_expanded, REP_PIPE, '|');
	replace_characters(command->input_expanded, REP_AND, '&');
	iter_special_replace(command);
	// ptr = ft_strchr(command->input_expanded, REP_DQ);
	// if (ptr && ptr[1] != REP_DQ)
	// 	truncate_character(command->input_expanded, 2);
	// ptr = ft_strchr(command->input_expanded, REP_SQ);
	// if (ptr && ptr[1] != REP_SQ)
	// 	truncate_character(command->input_expanded, 1);
	cmd_args = ft_split(command->input_expanded, REP_SPACE);
	if (!cmd_args && command->settings.expansion == false)
		handle_error(E_MALLOC, NULL, __func__);
	return (cmd_args);
}

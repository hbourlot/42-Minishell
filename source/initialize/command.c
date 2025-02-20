/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/20 14:51:41 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_command_input(t_shell *data, const char *delimiters[])
{
	sort_strings_by_length_desc((char **)delimiters);
	data->rl_splitted = split_by_multiple_tokens(data->rl, delimiters);
	if (!data->rl_splitted)
		handle_error(E_MALLOC, NULL, __func__);
}

static int	create_command_list(t_shell *data, const char *delimiters[])
{
	t_token	id;
	int		i;
	int		idx;
	char	*src;
	int		match_result;

	i = 0;
	src = data->rl;
	while (data->rl_splitted[i])
	{
		src = ft_strstr_any(src, delimiters);
		match_result = find_string_match(src, delimiters, &idx);
		if (match_result == CMP_OK)
		{
			id = get_t_token((char *)delimiters[idx],
					ft_strlen(delimiters[idx]));
			src += ft_strlen(delimiters[idx]);
		}
		else
			id = NO_TOKEN;
		add_command(&data->command, data->rl_splitted[i++], data, id);
	}
	data->nbr_of_commands = i;
	return (SUCCESS);
}


int	init_command(t_shell *data)
{
	const char	*delimiters[] = {"||", "|", "&&", NULL};
	size_t 		next_offset;
	size_t		prev_offset;

	if (data->rl)
	{
		split_command_input(data, delimiters);
		create_command_list(data, delimiters);
		next_offset = get_offset(data->command, &data->command->next);
		prev_offset = get_offset(data->command, &data->command->prev);
		init_prev(data->command, prev_offset, next_offset);
	}
	return (0);
}

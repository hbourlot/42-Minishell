/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/11 14:27:59 by joralves         ###   ########.fr       */
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

static bool	there_is_no_command(t_shell *data)
{
	const char	*tokens[] = {"||", "|", "&&", ">>", "<<", "<", ">", NULL};
	int			i;
	int			idx;
	int			match;

	i = 0;
	while (data->rl[i])
	{
		while (data->rl[i] == REP_SPACE)
			i++;
		match = find_string_match(&data->rl[i], tokens, &idx);
		if (data->rl[i] && match == -1)
			return (false);
		if (match != -1)
		{
			i += ft_strlen(tokens[idx]);
			if (!data->rl[i])
				break ;
		}
	}
	return (true);
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

static void	handle_eof(t_shell *data)
{
	const char	*eof_token[] = {"<<", NULL};

	if (initialize_eof(data) < 0)
		handle_error(E_MALLOC, NULL, __func__);
	strip_redirects(data->rl, eof_token);
	if (there_is_no_command(data))
		free_pointers(1, &data->rl);
}

int	init_command(t_shell *data)
{
	const char	*delimiters[] = {"||", "|", "&&", NULL};

	handle_eof(data);
	if (data->rl)
	{
		split_command_input(data, delimiters);
		create_command_list(data, delimiters);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:56:36 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/12 10:49:03 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static bool	is_valid_block(char *input, int *i)
{
	if (input[*i] == '-')
		(*i)++;
	while (input[*i] && input[*i] == 'n')
		(*i)++;
	return (input[*i] == '\0' || input[*i] == REP_SPACE);
}

static void	skip_spaces_with_idx(char *input, int *i)
{
	while (input[*i] == REP_SPACE)
		(*i)++;
}

static bool	process_flag_blocks(char *input, int *i)
{
	int		start;
	bool	cd;

	cd = false;
	while (input[*i] == '-')
	{
		start = *i;
		if (is_valid_block(input, i))
		{
			truncate_range(&input, start, *i - start);
			cd = true;
			*i = start;
		}
		else
			return (cd);
		skip_spaces_with_idx(input, i);
	}
	return (cd);
}

bool	is_echo_initialized(t_cmd *cmd)
{
	int	i;

	i = 0;
	skip_spaces_with_idx(cmd->input, &i);
	if (ft_strncmp(&cmd->input[i], "echo", 4) != 0)
		return false;
	i += 4;
	skip_spaces_with_idx(cmd->input, &i);
	return process_flag_blocks(cmd->input, &i);
}

int	main(void)
{
	t_cmd cmd;

	cmd.input = ft_strdup("echo -n -nnnnnnnn -n -n -nnnnnnnnnnnnnnnnnnn a");
	identify_and_replace_sq_tokens(&cmd.input);
	if (is_echo_initialized(&cmd))
	{
		printf("%s\n", cmd.input);
	}
	else
		printf("not init\n");
	restore_original_characters(&cmd.input);
	printf("%s\n", cmd.input);
	return (0);
}


// void	validate_builtin(t_shell *data, t_cmd *cmd)
// {
// 	is_echo(cmd->input)
// }

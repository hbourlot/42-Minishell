/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:56:36 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/23 00:34:08 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


bool is_echo_initialized(t_cmd *cmd)
{
	int		i;
	char 	*src;
	int		has_flags;

	has_flags = false;
	src = ft_strdup(cmd->input);
	if (!src)
	{	
		set_error_initialize(1, "Malloc", __func__, true);
		handle_error();
	}
	truncate_character(src, REP_DOUBLE_QUOTE);
	truncate_character(src, REP_SINGLE_QUOTE);
	skip_character_by_idx(src, REP_SPACE, &i);
	if (ft_strncmp("echo", &src[i], 4) != CMP_OK)
		return false;
	i+=4;
	while (src[i])
	{
		if (src[i] == '-')
		{
			i++;
			while (src[i] == 'n')
				i++;
			if (src[i]  && src[i] != REP_SPACE)
				has_flags = false;
			skip_character_by_idx(src, REP_SPACE, &i);
			// if (has_flags);
				
		}
	}
	return false;
}

int	main(void)
{
	t_cmd 	cmd;
	char	*tmp;

	cmd.input = ft_strdup("'echo' -n -nnnnnnnn -n -n -nnnnnnnnnnnnnnn $PATH nnnn oi");
	identify_and_replace_sqpa_tokens(cmd.input);
	if (is_echo_initialized(&cmd))
	{
		truncate_character(cmd.input, REP_SPACE);
		truncate_character(cmd.input, REP_DOUBLE_QUOTE);
		truncate_character(cmd.input, REP_SINGLE_QUOTE);
		tmp = cmd.input += 4;
		printf("%s", tmp);
	}
	else
		printf("not init\n");
	// printf("%s\n", cmd.input);
	return (0);
} 

// void	validate_builtin(t_shell *data, t_cmd *cmd)
// {
// 	is_echo(cmd->input)
// }

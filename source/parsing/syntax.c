/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/02 22:37:07 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Parses the input string to validate its syntax.
///        Specifically checks for invalid token sequences
///         and reports syntax errors.
/// @param input The input string to parse.
/// @return 0 if the input is valid; -1 if a syntax error is detected.
int	parsing_syntax(t_shell *data)
{
	// const char *pipe_tokens[] = {"||", "|", NULL};
	// const char *redirect_tokens[] = {"<<", ">>", ">", "<", NULL};
	// int			fd_id[2];

	// fd_id[1] = STDOUT_FILENO;
	if (is_valid_pipe_tokens(data->readline) == false || 
		is_valid_file_and_here_doc_tokens(data->readline) == false ||
		is_quotes_maching(data->readline) == false)
		{
			data->exit_status = 2;
			return (-1);
		}
	
	// if (data->it_ends_with_delimiter)
	// {
	// 	data->eof = ft_split(" ", ' ');
	// 	if (!data->eof)
	// 	{
	// 		return (-1);
	// 	}
	// 	here_doc(fd_id, NULL);
	// }
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:41:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 15:20:17 by hbourlot         ###   ########.fr       */
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
	if (is_tokens_invalid(data->rl) 
		|| is_quotes_matching(data->rl) == false)
	{
		data->exit_status = 2;
		return -1;
	}
	return (0);
}

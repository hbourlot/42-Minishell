/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:43:23 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/15 10:45:53 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_exit(t_cmd *cmd)
{
	if (cmd->input && ft_strcmp("exit", cmd->input) == CMP_OK)
	{
		cmd->settings.builtin_exit = true;
		return (true);
	}
	return (false);
}

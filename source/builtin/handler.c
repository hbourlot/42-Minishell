/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:41:34 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/15 10:43:14 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_builtin(t_cmd *cmd)
{
	if (builtin_echo(cmd))
		return (1);
	if (builtin_exit(cmd))
		return (1); 
}
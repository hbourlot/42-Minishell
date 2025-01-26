/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:41:34 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/22 00:05:33 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// hbourlot@c65c2c36c642:~/Projects/minishell$ ./minishell
// minishell$> "exit" ls
// Minishell: exit: ls: numeric argument required
// hbourlot@c65c2c36c642:~/Projects/minishell$

// minishell$> exit :
// Minishell: exit: :: numeric argument required
// hbourlot@c65c2c36c642:~/Projects/minishell$ echo $?

// exit_status 2

int	process_builtin(t_cmd *cmd)
{
	if (builtin_echo(cmd))
		return (1);
	if (builtin_exit(cmd))
		return (1); 
}
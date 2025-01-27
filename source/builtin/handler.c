/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:41:34 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/25 18:05:08 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_is_builtin(t_shell *data, t_cmd *last_node)
{
	char		*command;
	int			i;
	const char	*builtin_functions[] = {"cd", "export", "display","unset", "exit", NULL};
	bool		*builtin_flags[] = {&last_node->settings.builtin_cd,
				&last_node->settings.builtin_export,
				&last_node->settings.builtin_display,
				&last_node->settings.builtin_unset,
				&last_node->settings.builtin_exit};

	i = 0;
	command = last_node->args[0];
	if (!command || !*command || all_same_char(command, ' '))
		return ;
	while (builtin_functions[i])
	{
		if (ft_strcmp(command, builtin_functions[i]) == 0)
		{
			*builtin_flags[i] = true;
			break ;
		}
		i++;
	}
}


// int	process_builtin(t_cmd *cmd)
// {
// 	if (builtin_echo(cmd))
// 		return (1);
// 	if (builtin_exit(cmd))
// 		return (1); 
// }
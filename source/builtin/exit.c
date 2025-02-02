/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:43:23 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/30 20:55:38 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/// @brief Handles the `exit` built-in command to terminate the shell.
/// @param data The shell structure containing environment and state.
/// @param cmd The command structure with arguments for `exit`.
/// @details Exits the shell, handling optional numeric exit codes.
///          - If more than one argument is provided, sets `exit_status` to 1 and returns.
///          - If a non-numeric argument is given, prints an error, cleans up, and exits with status 2.
///          - Otherwise, exits with the provided numeric value or 0 if none is given.
void	builtin_exit(t_shell *data, t_cmd *cmd)
{
	int	len;
	int	ret;

	len = array_length(cmd->args);
	if (len > 2)
	{
		data->exit_status = 1;
		return ;
	}
	else if (len == 2)
	{
		if (!is_numeric(cmd->args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", cmd->args[1]);
			cleanup_shell(data);
			exit(2);
		}
		ret = ft_atoi(cmd->args[1]);
		cleanup_shell(data);
		exit(ret);
	}
	cleanup_shell(data);
	exit(0);
}

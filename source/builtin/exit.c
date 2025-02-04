/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:43:23 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/04 17:05:43 by joralves         ###   ########.fr       */
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

/// @brief Handles `exit` to terminate the shell.
/// @param data The shell structure with environment and state.
/// @param cmd The command structure with arguments.
/// @details Exits with an optional numeric code.
///          - Multiple args set `exit_status` to 1 and return.
///          - Non-numeric args print an error, clean up, and exit with 2.
///          - Otherwise, exits with the given code or 0.

void	builtin_exit(t_shell *data, t_cmd *cmd)
{
	int	len;
	int	ret;

	len = array_length(cmd->args);
		printf("exit\n");
	if (len > 2)
	{
		ft_printf_error("bash: exit: too many arguments\n");
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

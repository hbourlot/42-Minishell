/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:43:23 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/08 15:25:54 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str, long long *ret)
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
		if (i > 19 && (str[0] != '+' || str[0] != '-'))
			return (0);
		if (i > 20 && (str[0] == '+' || str[0] == '-'))
			return (0);
		i++;
	}
	*ret = ft_atoll(str);
	if (*ret < LONG_MIN || *ret > LONG_MAX)
		return (0);
	return (1);
}

static void	exit_with_error(t_shell *data, const char *arg)
{
	ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", arg);
	cleanup_shell(data);
	exit(2);
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
	int			len;
	long long	ret;

	len = array_length(cmd->args);
	printf("exit\n");
	if (len > 2)
	{
		if (!is_numeric(cmd->args[1], &ret))
			exit_with_error(data, cmd->args[1]);
		ft_printf_fd(2, "bash: exit: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	else if (len == 2)
	{
		if (!is_numeric(cmd->args[1], &ret))
			exit_with_error(data, cmd->args[1]);
		cleanup_shell(data);
		exit(ret);
	}
	cleanup_shell(data);
	exit(0);
}

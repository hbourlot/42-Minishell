/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:00:45 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/19 16:33:50 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	get_shell()->exit_status = 130;
}

void	setup_parent_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	cleanup_shell(get_shell());
	write(2, "\n", 1);
	exit(130);
}

void	handle_sigquit_child(int sig)
{
	(void)sig;
	cleanup_shell(get_shell());
	write(2, "\n", 1);
	exit(131);
}

void	restore_signals(int code)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint_child;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	if (code == EOF)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, handle_sigint_child);
}

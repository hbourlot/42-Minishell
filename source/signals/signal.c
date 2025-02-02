/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:00:45 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/01 23:13:38 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_shell()->exit_status = 130;
		// refresh_shell_data(get_shell());
	}
}

void	sigint_heredoc_handler(int signal)
{
	(void)signal;
	close(get_shell()->pipe_id[0]);
	close(get_shell()->pipe_id[1]);
	cleanup_shell(get_shell());
	write(1, "\n", 1);
	exit(130);
}
void	setup_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


void	handle_signals(t_shell *data, int status)
{
	if (status == 1)
	{
		signal(SIGINT, sigint_heredoc_handler);
	}

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:58:02 by joralves          #+#    #+#             */
/*   Updated: 2025/01/30 20:53:18 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	sigint_heredoc_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(1);
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

// Todo: Need to fix case of cat then CTRL+C :  undefined behavior
int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*data;

	setup_signals();
	data = init_shell(argc, argv, envp);
	if (main_shell_loop(data))
		return (cleanup_shell(data), handle_error());
	cleanup_shell(data);
	return (0);
}

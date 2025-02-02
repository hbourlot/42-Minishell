/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:58:02 by joralves          #+#    #+#             */
/*   Updated: 2025/02/02 17:52:55 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1); // Nueva línea
	rl_on_new_line();
	// Indicar a readline que estamos en nueva línea
	rl_replace_line("", 0); // Limpiar línea actual
	rl_redisplay();         // Volver a mostrar el prompt
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

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// Todo: Need to fix case of cat then CTRL+C :  undefined behavior
int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*data;

	data = init_shell(argc, argv, envp);
	if (main_shell_loop(data))
		return (cleanup_shell(data), handle_error());
	cleanup_shell(data);
	return (0);
}

//   signal(SIGINT, SIG_DFL);
//         signal(SIGQUIT, SIG_DFL);
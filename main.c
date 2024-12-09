/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/09 16:40:35 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_signals(int signal)
// {
// 	if (signal == SIGINT || signal == SIGQUIT)
// 	{
// 		printf("\n");
// 		return ;
// 	}
// }

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_shell				*data;
// 	char				*input;
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = handle_signals;
// 	sa.sa_flags = 0;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	sigaction(SIGINT, &sa, NULL);
// 	data = get_shell();
// 	if (init_program(data))
// 		return (1); // ! Error managing here
// 	cleanup_shell(data);
// 	return (0);
// }

// char *test[] = {"echo", "$PATH", NULL};
// execve("/bin/echo", test, NULL);

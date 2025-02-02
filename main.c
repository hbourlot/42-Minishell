/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:58:02 by joralves          #+#    #+#             */
/*   Updated: 2025/02/02 18:17:54 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
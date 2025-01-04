/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/30 17:36:31 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// static void cleanup_readline() {
//     clear_history();        // Frees history list memory
//     rl_clear_signals();     // Clears signal handlers
//     rl_cleanup_after_signal(); // Cleans up after any signals
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;
	char 		*input;

	// cleanup_readline();
	data = init_shell(argc, argv, envp);
	if (main_shell_loop(data))
		return (handle_error());
	cleanup_shell(get_shell());
	return 0;
}


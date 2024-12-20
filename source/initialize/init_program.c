/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:01:57 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/20 16:31:31 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	run_shell(t_shell *data, char *input)
{
	if (init_command(input))
		return (-1); // TODO: ADD a message that failed to create command :)
	// printf("-- DEBUG --\n");
	// debug_command_path(data);
	// debug_command_input(data);
	// debug_command_args(data);
	// printf("-- END --\n");
	execution(data);
	cleanup_shell(data);
	return (0);
}

/// @brief Main loop of the shell program. Reads user input and processes it.
/// @param data Pointer to the shell structure.
/// @return 0 on success, -1 on error or when exiting.
int	init_program(t_shell *data)
{
	char *input;

	input = NULL;
	while (true)
	{
		input = readline("minishell-> ");
		// if (input == NULL)
		// TODO: Need to add input line to the history here!
		if (run_shell(data, input))
			return (free(input) , -1);
		free(input);
	}
	return (0);
}

/// @brief Provides access to a singleton instance of the shell structure.
/// @return A pointer to the singleton `t_shell` instance.
t_shell *get_shell()
{
	static t_shell data;
	return (&data);
}

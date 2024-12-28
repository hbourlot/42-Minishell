/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:01:57 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/27 08:41:53 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

	// printf("-- DEBUG --\n");
	// debug_command_path(data);
	// debug_command_input(data);
	// debug_command_args(data);
	// printf("-- END --\n");

static int	run_shell(t_shell *data, char *input)
{
	bool run;

	run = true;
	if (parsing_syntax(input) == ERROR)
	{
		handle_error_parsing();
		run = false;
	}
	if (run == true && init_command(input) == ERROR)
		return (ERROR); // TODO: Here i can exit the program: But still need to check deeply in get_path and args case
	if (run == true)
		run_commands(data);
	refresh_shell_data(data);
	return (SUCCESS);
}

/// @brief Main loop of the shell program. Reads user input and processes it.
/// @param data Pointer to the shell structure.
/// @return 0 on success, -1 on error or when exiting.
// int	init_program(t_shell *data)
// {
// 	char *input;

// 	input = NULL;
// 	while (true)
// 	{
// 		input = readline("minishell-> ");
// 		// if (input == NULL)
// 		// TODO: Need to add input line to the history here!
// 		if (ft_strlen(input) == 0)
// 		{
// 			printf("\n");
// 			continue;
// 		}
// 		if (run_shell(data, input))
// 			return (free(input), handle_error_parsing(), ERROR);
// 		free(input);
// 	}
// 	return (SUCCESS);
// }

int	init_program(t_shell *data)
{
	// while (true)
	// {
		// if (input == NULL)
		// TODO: Need to add input line to the history here!
		char *src = "ls";
		char *input = ft_strdup(src);
		// char *input = get_next_line(STDIN_FILENO);
		// printf("input: %s\n", input);
		if (ft_strlen(input) == 0)
		{
			printf("\n");
			return (0);
			// continue;
		}
		if (run_shell(data, input))
			return (free(input), ERROR);
		free(input);
	// }
	return (SUCCESS);
}



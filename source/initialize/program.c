/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:01:57 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 12:26:34 by hbourlot         ###   ########.fr       */
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
	if (parsing_syntax(input) == ERROR)
		return (ERROR);
	if (init_command(input) == ERROR)
		return (ERROR); // TODO: ADD a message that failed to create command :)
	run_commands(data);
	refresh_shell_data(data);
	return (SUCCESS);
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
		if (ft_strlen(input) == 0)
		{
			printf("\n");
			continue;
		}
		if (run_shell(data, input))
			return (free(input), handle_error(), ERROR);
		free(input);
	}
	return (SUCCESS);
}

// int	init_program(t_shell *data)
// {
// 	// char *input;
// 	static int i = 0;
// 	// input = NULL;
// 	while (true)
// 	{
// 		i++;
// 		if (i == 4)
// 			break;
// 		// input = readline("minishell-> ");
// 		// if (input == NULL)
// 		// TODO: Need to add input line to the history here!
// 		char *src = "ls > file < file2 < file3 >file4 oi oi >file5>file6<file7 oi oi";
// 		// char *input = get_next_line(STDIN_FILENO);
// 		char *input = ft_strdup(src);
// 		// printf("input: %s\n", input);
// 		if (ft_strlen(input) == 0)
// 		{
// 			printf("\n");
// 			return (0);
// 			// continue;
// 		}
// 		if (run_shell(data, input))
// 			return (free(input), ERROR);
// 		free(input);
// 	}
// 	return (SUCCESS);
// }

/// @brief Provides access to a singleton instance of the shell structure.
/// @return A pointer to the singleton `t_shell` instance.
t_shell *get_shell()
{
	static t_shell data;
	return (&data);
}

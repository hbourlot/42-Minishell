/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:01:57 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/27 19:13:46 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	run_shell(t_shell *data, char *input)
{
	data->input_splitted = ft_split(input, '|');
	if (data->input_splitted == NULL)
		return (printf("data->input_splitted Error\n"), -1); // ! Error managing here
	data->command = create_command_list(data->input_splitted);
	if (!data->command)
		return (printf("create_command_list Error\n"), -1); // ! Error managing here
	if (initialize_command(data->input_splitted, data->command))
		return (printf("initialize_command Error\n"), -1); // ! Error managing here
	debug_command_precommand(data);
	debug_command_args(data);
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
		if (input == NULL)
		{
			printf("\nExiting..\n");
			return (free(input), 0);
		}
		// TODO: Need to add input line to the history here!
		if (run_shell(data, input))
			return (free(input), -1);
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
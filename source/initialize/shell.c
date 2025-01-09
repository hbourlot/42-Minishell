/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:20 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/07 12:00:38 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_shell(t_shell *data, char *input)
{
	bool run;

	run = true;
	if (parsing_syntax(input) == ERROR)
	{
		handle_error_parsing();
		run = false;
	}
	if (run && init_command(input) == ERROR)
		return (ERROR);
	if (run)
		run_commands(data);
	refresh_shell_data(data);
	return (SUCCESS);
}

/// @brief Main loop of the shell program. Reads user input and processes it.
/// @param data Pointer to the shell structure.
/// @return 0 on success, -1 on error or when exiting.
int	main_shell_loop(t_shell *data)
{
	// char *input;

	// input = NULL;
	while (true)
	{
		data->readline = readline("[Xitaozinho&Xororo@localhost ~]$ ");
		// TODO: Need to add input line to the history here!
		if (ft_strlen(data->readline) == 0 || all_same_char(data->readline, ' '))
		{
			free(data->readline);
			printf("\n");
			continue;
		}
		if (ft_strcmp("exit", data->readline) == CMP_OK)
		{
			printf("exit\n");
			break;
		}
		if (run_shell(data, data->readline))
			return (free(data->readline), handle_error_parsing(), ERROR);
		free(data->readline);
	}
	return (0);
}

// int	main_shell_loop(t_shell *data)
// {
// 	// while (true)
// 	// {
// 		// if (input == NULL)
// 		// TODO: Need to add input line to the history here!
// 		// char *src = " >        file >             file1 >file2 <file3";
// 		char *src = "<< file";
// 		data->readline = ft_strdup(src);
// 		// char *input = get_next_line(STDIN_FILENO);
// 		// printf("input: %s\n", input);
// 		if (ft_strlen(data->readline) == 0 || all_same_char(data->readline, ' '))

// 		{
// 			printf("\n");
// 			return (0);
// 			// continue;
// 		}
// 		if (run_shell(data, data->readline))
// 			return (free(data->readline), ERROR);
// 	// }
// 	return (SUCCESS);
// }

t_shell	*init_shell(int argc, char *argv[], char *envp[])
{
	t_shell *data;
	
	data = get_shell();
	// ft_memset(data, 0, sizeof(t_shell));
	// data->input_splitted = NULL;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
    if (initialize_environment_paths(data))
    {
        cleanup_shell(data);
        exit(EXIT_FAILURE); // TODO: Add a custom message ??
    }
	return (data);
}

/// @brief Provides access to a singleton instance of the shell structure.
/// @return A pointer to the singleton `t_shell` instance.
t_shell *get_shell()
{
	static t_shell data;
	return (&data);
}

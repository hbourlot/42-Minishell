/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:20 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/28 16:26:05 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	initialize_environment_paths(t_shell *data)
{
	int			i;

	i = 0;
	if (!data->envp || !*data->envp)
	{
		data->env_paths = NULL;
		return (SUCCESS);
	}
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == CMP_OK)
		{
			if (ft_strlen(data->envp[i] + 5) == 0)
				data->env_paths = NULL;
			else
            {
				data->env_paths = ft_split(data->envp[i] + 5, ':');
                if (!data->env_paths)
                    return (ERROR); 
            }
			break ;
		}
		i++;
	}
    return (SUCCESS);
}

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
		return (ERROR);  // TODO: Handle `get_path` and args errors here
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
	char *input;

	input = NULL;
	while (true)
	{
		input = readline("[Xitaozinho&Xororo@localhost ~]$ ");
		// if (input == NULL)
		// TODO: Need to add input line to the history here!
		if (ft_strlen(input) == 0)
		{
			printf("\n");
			continue;
		}
		if (run_shell(data, input))
			return (free(input), handle_error_parsing(), ERROR);
		free(input);
	}
	return (SUCCESS);
}

// int	main_shell_loop(t_shell *data)
// {
// 	// while (true)
// 	// {
// 		// if (input == NULL)
// 		// TODO: Need to add input line to the history here!
// 		char *src = "ls";
// 		char *input = ft_strdup(src);
// 		// char *input = get_next_line(STDIN_FILENO);
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

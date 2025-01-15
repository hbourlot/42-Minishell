/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:20 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/15 17:00:59 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_shell(t_shell *data, char *input)
{
	bool	run;

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
	char	**args;

	while (true)
	{
		data->readline = readline("[Chitãozinho&Xororó@localhost ~]$ ");
		if (data->readline && *data->readline)
			add_history(data->readline);
		if (!data->readline || ft_strcmp("exit", data->readline) == CMP_OK)
			return (printf("exit\n"), 0);
		if (ft_strncmp("cd", data->readline, 2) == CMP_OK)
		{
			identify_and_replace_sq_tokens(&data->readline);
			args = process_command_input(data->readline);
			ft_cd(args);
			continue;
		}
		if (ft_strlen(data->readline) == 0 || all_same_char(data->readline,
				' '))
		{
			free(data->readline);
			printf("\n");
			continue ;
		}
		if (run_shell(data, data->readline))
			return (ERROR);
		free(data->readline);
	}
	return (0);
}

t_shell	*init_shell(int argc, char *argv[], char *envp[])
{
	t_shell	*data;

	data = get_shell();
	// ft_memset(data, 0, sizeof(t_shell));
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
t_shell	*get_shell(void)
{
	static t_shell	data;

	return (&data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:31:29 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/04 12:16:09 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	verify_and_prepare_input(t_shell *data)
{
	if (data->readline && *data->readline)
		add_history(data->readline);
	identify_and_replace_sqpa_tokens(data->readline);
	if (all_same_char(data->readline, REP_SPACE))
	{
		free_pointers(1, &data->readline);
		return (false);
	}
	if (parsing_syntax(data) == -1)
		return (false);
	if (init_command(data) == -1)
		return (false);
	return (true);
}

int	main_shell_loop(t_shell *data)
{
	while (true)
	{
		setup_parent_signals();
		data->readline = readline(PROMPT);
		if (!data->readline)
			return (printf("exit\n"), 0);
		if (verify_and_prepare_input(data) == false)
			handle_error();
		else if (data->command || data->eof)
			run_commands(data);
		refresh_shell_data(data);
	}
	return (0);
}

t_shell	*init_shell(int argc, char *argv[], char *envp[])
{
	t_shell	*data;

	data = get_shell();
	data->argc = argc;
	data->argv = argv;
	data->map = create_map();
	data->pid = -1;
	data->prev_fd = -1;
	ft_memset(data->pipe_id, -1, 8);
	if (import_env_to_hashmap(data->map, envp) == -1
		|| update_envp_and_envpath(data) == -1)
	{
		cleanup_shell(data);
		exit(EXIT_FAILURE);
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

t_hashmap	*create_map(void)
{
	static t_hashmap	map;

	return (&map);
}

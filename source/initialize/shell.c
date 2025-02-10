/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:31:29 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 16:55:40 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	verify_and_prepare_input(t_shell *data)
{
	if (data->rl && *data->rl)
	{
		add_history(data->rl);
		data->nbr_of_lines += 1;
	}
	identify_and_replace_sqpa_tokens(data->rl);
	if (all_same_char(data->rl, REP_SPACE))
		return (free_pointers(1, &data->rl));
	if (parsing_syntax(data) == -1)
		return ;
	if (init_command(data) == -1)
		return ;
}

int	main_shell_loop(t_shell *data)
{
	while (true)
	{
		setup_parent_signals();
		data->rl = readline(PROMPT);
		if (!data->rl)
			return (printf("exit\n"), 0);
		verify_and_prepare_input(data);
		if (data->command || data->eof)
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
	import_env_to_hashmap(data->map, envp);
	update_envp_and_envpath(data);
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

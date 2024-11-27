/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/27 17:46:42 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/// @brief Provides access to a singleton instance of the shell structure.
/// @return A pointer to the singleton `t_shell` instance.
t_shell *get_shell()
{
	static t_shell data;
	return (&data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;


	while (true)
	{
		data = get_shell();
		data->input_splitted = ft_split(readline(""), '|');
		if (data->input_splitted == NULL)
		{
			printf("\nExiting...\n");
			break;
		}
		data->command = create_command_list(data->input_splitted);
		if (initialize_command(data->input_splitted, data->command))
			return (1);
		debug_command_precommand(data);
		debug_command_args(data);
		cleanup_shell(&data);
	}
	cleanup_shell(&data);
	return 0;
}


	// char *test[] = {"echo", "$PATH", NULL};
	// execve("/bin/echo", test, NULL);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/06 00:35:49 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	init_shell(int argc, char *argv[], char *envp[])
{
	t_shell *data;
	
	data = get_shell();
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
}


int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;
	char 		*input;
	const char *delimiters[] = {"||", "&&", "|", NULL};

	init_shell(argc, argv, envp);
	if (init_command("||||||||||||||||||||||||||||||| ", delimiters))
		printf("error on create\n");
	debug_command_args(get_shell());
	debug_command_input(get_shell());
	return 0;
}

// void	exc_echo(t_cmd *cmd)
// {
// 	cmd->path = ft_strdup("/bin/echo");
// 	cmd->args = "aqui precisa dos argumentos que vc esta criando, mas o args[0] precisa ser -> echo";
// 	// TODO exs: {"echo", "abc", "NULL"};
// 	// TODO exs: {"echo", "abc", "a", "NULL"};
// 	// TODO exs: {"echo", "abcz", "'a'", "NULL"};
// 	execve(cmd->path, cmd->args, cmd->envp);
// }






	// debug_command_input(get_shell());
	// data = get_shell();
	// if (init_program(data))
	// 	return (1); // ! Error managing here
	// cleanup_shell(data);






	// char *test[] = {"echo", "$PATH", NULL};
	// execve("/bin/echo", test, NULL);


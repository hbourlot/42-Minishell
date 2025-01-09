/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/09 15:49:44 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

// int	prepare_execve_parameters(t_shell *data, char **input) // TODO: from command->input
// {	
	// identify_and_replace_quotes(input);
// 	int	i = 0;
// 	while ((*input)[i])
// 	{
// 		if ((*input)[i] == REP_DOUBLE_QUOTE)
// 			printf("2");
// 		if ((*input)[i] == REP_SINGLE_QUOTE)
// 			printf("1");
// 		if ((*input)[i] == REP_SPACE)
// 			printf("3");
// 		else
// 			printf("%c", (*input)[i]);
// 		i++;
// 	}
// 	return (0);
// }


// int	get_path(char **input)
// {
// 	int	start;
// 	int	end;
// 	char *file;
// 	char	*expand;

// 	end = 0;
// 	start = 0;
// 	while (input[start] == REP_SPACE)
// 		start++;
// 	end = start;
// 	while (input[end] && input[end] != REP_SPACE)
// 		end++;
// 	file = ft_substr(input, start, end - start);
// 	return (0);
// }

int	main(int argc, char *argv[], char *envp[])
{
	struct sigaction	sa;
	t_shell				*data;
	char				*input;

	data = get_shell();
	data->readline = readline("[minishell@hostname ~] ");
	if (prepare_execve_parameters(data, &data->readline))
	{
		perror("ERROR");
		return (1);
	}
	return (0);






	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	data = init_shell(argc, argv, envp);
	if (main_shell_loop(data))
		return (handle_error());
	cleanup_shell(get_shell());
	return 0;
}
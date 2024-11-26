/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/26 15:44:24 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	initialize_tokens(t_cmd_tokens *tokens, char *cmd_line)
{
	int		i;
	char 	*pointer_to_pipe;
	
	i = 0;
	while (ft_strchr(cmd_line, '|') /* && !ft_strchr(cmd_line, START_OF_TEXT) */)
	{
		pointer_to_pipe = ft_strchr(cmd_line, '|');
		*pointer_to_pipe = START_OF_TEXT;
		tokens->nbr_of_cmds += 1;
	}
	if (ft_strchr(cmd_line, START_OF_TEXT))
		tokens->nbr_of_cmds += 1;
}


int	main(int argc, char *argv[], char *envp[])
{
	t_data *data;
	char	*buffer;
	t_cmd_tokens	tokens;

	ft_bzero(&tokens, sizeof(t_cmd_tokens));
	data->running = true;

	while (data->running)
	{
		write(1, "minishell-> ", 13);
		char *cmd_line = get_next_line(0);
		char **args = get_args(cmd_line);
		for (int i = 0; i < 20 && args[i]; i++)
			printf("arg: %s\n", args[i]);
	}
	
	// char *cmds[] = {"echo", "'test'", NULL};
	// execve("/bin/echo", cmds, NULL);
	
	return 0;
}
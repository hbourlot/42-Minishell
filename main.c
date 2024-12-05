/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/04 16:04:32 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_shell		*data;
// 	char 		*input;

// 	data = get_shell();
// 	if (init_program(data))
// 		return (1); // ! Error managing here
// 	cleanup_shell(data);
// 	return (0);
// }

typedef struct s_command
{
	char	*command;
	char	*flag;
	char	*argument;
	bool	expand;
}			t_command;

int	split_in_string(t_command *command, char *str)
{
	int		i;
	int		start;
	bool	in_single;
	bool	in_double;

	i = 0;
	start = 0;
	in_single = false;
	in_double = false;
	while (str && str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			command->expand = false;
			in_single = !in_single;
		}
		if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		if ((str[i] == ' ' && !in_single && !in_double) || str[i + 1] == '\0')
		{
			if (!command->command)
				command->command = ft_substr(str, start, i - start);
			else if (!command->flag)
				command->flag = ft_substr(str, start, i - start);
			else if (!command->argument)
				command->argument = ft_substr(str, start, i - start);
			start = i + 1;
		}
		i++;
	}
}

char	*expand_aux(char *str)
{
	char	*temp;
	char	**splited;
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	splited = ft_split(str, '$');
	while (splited[i])
	{
		temp = getenv(splited[i]);
		res = ft_append_and_free(res, temp);
		free(splited[i]);
		i++;
	}
	free(splited);
	free(str);
	return (res);
}

void	expand_var(t_command *command)
{
	char	**splited;
	char	*str;
	char	*expanded;
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	if (!command->argument || command->expand == false
		|| !ft_strchr(command->argument, '$'))
		return ;
	str = command->argument;
	splited = ft_split_charset(str, " \"");
	while (splited[i])
	{
		if (ft_strchr(splited[i], '$'))
			splited[i] = expand_aux(splited[i]);
		res = ft_append_and_free_charset(res, splited[i], ' ');
		free(splited[i]);
		i++;
	}
	free(splited);
	free(str);
	command->argument = res;
}

int	main(void)
{
	char		*dest;
	t_command	command;
	int			fd;

	ft_bzero(&command, sizeof(t_command));
	command.expand = true;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error opening file", 2), 1);
	dest = get_next_line(fd);
	free(dest);
	dest = get_next_line(fd);
	split_in_string(&command, dest);
	expand_var(&command);
	printf("%s\n%s\n%s\n", command.command, command.flag, command.argument);
	free(command.argument);
	free(command.command);
	free(command.flag);
	free(dest);
}

// char *test[] = {"echo", "$PATH", NULL};
// execve("/bin/echo", test, NULL);

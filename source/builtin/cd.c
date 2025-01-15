/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:57:27 by joralves          #+#    #+#             */
/*   Updated: 2025/01/15 17:13:45 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// #include <stdio.h>
// #include <unistd.h>

int	ft_cd(char **command_args)
{
	int	i;

	i = 0;
	while (command_args[i])
	{
		// printf("command-args %s\n", command_args[i]);
		i++;
	}
	if (i == 1)
	{
		chdir(getenv("HOME"));
	}
	else if (i > 2)
		printf("bash: cd: too many arguments\n");
	else
	{
		if (chdir(command_args[1]) != 0)
		{
			printf("bash: cd: %s: Not a directory\n", command_args[1]);
			return (-1);
		}
	}
	return (0);
}

// int	main(void)
// {
// 	char	s[100];

// 	// printing current working directory
// printf("%s\n", getcwd(s, 100));
// 	// using the command
// 	chdir("..");
// 	// printing current working directory
// 	printf("%s\n", getcwd(s, 100));
// 	// after chdir is executed
// 	return (0);
// }

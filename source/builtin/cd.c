/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:57:27 by joralves          #+#    #+#             */
/*   Updated: 2025/01/25 18:50:06 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// #include <stdio.h>
// #include <unistd.h>
//
// int	builtin_cd(t_shell *data, char **command_args)
// {
// 	int			arg_count;
// 	t_hashmap	*map;
// 	char		cwd[PATH_MAX + 1];
// 	char		*home;
// 	char		*temp_cwd;
//
// 	map = data->map;
// 	home = hashmap_search(map, "HOME");
// 	getcwd(cwd, PATH_MAX);
// 	arg_count = 0;
// 	temp_cwd = ft_strdup(cwd);
// 	if (!temp_cwd)
// 	{
// 		printf("MAlloc Fail\n");
// 		return (-1);
// 	}
// 	while (command_args[arg_count])
// 		arg_count++;
// 	if (arg_count == 1)
// 	{
// 		chdir(home);
// 		hashmap_insert(map, "OLDPWD", temp_cwd);
// 		free(temp_cwd);
// 		getcwd(cwd, PATH_MAX);
// 		temp_cwd = ft_strdup(cwd);
// 		if (!temp_cwd)
// 		{
// 			printf("MAlloc Fail\n");
// 			return (-1);
// 		}
// 		hashmap_insert(map, "PWD", temp_cwd);
// 		free(temp_cwd);
// 	}
// 	else if (arg_count > 2)
// 		printf("bash: cd: too many arguments\n");
// 	else
// 	{
// 		if (chdir(command_args[1]) != 0)
// 		{
// 			printf("bash: cd: %s: No such file or directory\n",
// 				command_args[1]);
// 			return (-1);
// 		}
// 		hashmap_insert(map, "OLDPWD", temp_cwd);
// 		free(temp_cwd);
// 		getcwd(cwd, PATH_MAX);
// 		temp_cwd = ft_strdup(cwd);
// 		if (!temp_cwd)
// 		{
// 			printf("MAlloc Fail\n");
// 			return (-1);
// 		}
// 		hashmap_insert(map, "PWD", temp_cwd);
// 		free(temp_cwd);
// 	}
// 	if (update_envp_and_envpath(data) != 0)
// 	{
// 		printf("MAlloc Fail\n");
// 		return (-1);
// 	}
// 	return (0);
// }

static int	change_directory(t_shell *data, const char *dir)
{
	t_hashmap	*map;
	char		cwd[PATH_MAX + 1];
	char		*temp_cwd;

	map = data->map;
	getcwd(cwd, PATH_MAX);
	if (chdir(dir) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", dir);
		return (1);
	}
	temp_cwd = ft_strdup(cwd);
	if (!temp_cwd)
		return (-1);
	hashmap_insert(map, "OLDPWD", temp_cwd);
	getcwd(cwd, PATH_MAX);
	temp_cwd = ft_strdup(cwd);
	if (!temp_cwd)
		return (-1);
	hashmap_insert(map, "PWD", temp_cwd);
	return (0);
}

int	builtin_cd(t_shell *data, char **command_args)
{
	t_hashmap	*map;
	char		*home;
	size_t		arg_count;

	map = data->map;
	home = hashmap_search(map, "HOME");
	arg_count = array_length(command_args);
	if (arg_count == 1)
	{
		if (change_directory(data, home) == -1)
			return (-1);
	}
	else if (arg_count > 2)
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	else
	{
		if (change_directory(data, command_args[1]) == -1)
			return (-1);
	}
	if (hashmap_to_env_array(data, map) == -1)
		return (-1);
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

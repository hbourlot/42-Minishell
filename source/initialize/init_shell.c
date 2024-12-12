/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:20 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/12 14:20:01 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_envp(t_shell *data)
{
	int			i;

	i = 0;
	if (!data->envp || !*data->envp)
	{
		data->env_paths = NULL;
		return (0);
	}
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == CMP_OK)
		{
			if (ft_strlen(data->envp[i] + 5) == 0)
				data->env_paths = NULL;
			else
            {
				data->env_paths = ft_split(data->envp[i] + 5, ':');
                if (!data->env_paths)
                    return (-1); 
            }
			break ;
		}
		i++;
	}
    return (0);
}

t_shell	*init_shell(int argc, char *argv[], char *envp[])
{
	t_shell *data;
	
	data = get_shell();
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
    if (get_envp(data))
    {
        cleanup_shell(data);
        exit(EXIT_FAILURE); // TODO: Add a custom message ??
    }
	return (data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/10 18:38:06 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static t_shell	*init_shell(int argc, char *argv[], char *envp[])
{
	t_shell *data;
	
	data = get_shell();
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;

	return (data);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;
	char 		*input;

	data = init_shell(argc, argv, envp);
	if (init_program(data))
		cleanup_shell(get_shell());

	return 0;
}

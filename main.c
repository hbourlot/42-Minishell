/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/25 11:30:09 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;
	char 		*input;

	data = init_shell(argc, argv, envp);
	if (init_program(data))
		return (cleanup_shell(get_shell()), handle_error());
	cleanup_shell(get_shell());
	return 0;
}


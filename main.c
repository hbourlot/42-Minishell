/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:58:02 by joralves          #+#    #+#             */
/*   Updated: 2025/02/01 22:12:26 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Todo: Need to fix case of cat then CTRL+C :  undefined behavior
int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*data;

	setup_signals();
	data = init_shell(argc, argv, envp);
	if (main_shell_loop(data))
		return (cleanup_shell(data), handle_error());
	cleanup_shell(data);
	return (0);
}

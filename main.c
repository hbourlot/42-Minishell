/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:58:02 by joralves          #+#    #+#             */
/*   Updated: 2025/02/23 16:36:05 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	*data;

	data = init_shell(argc, argv, envp);
	if (main_shell_loop(data))
		return (cleanup_shell(data), handle_error(0, NULL, NULL));
	cleanup_shell(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/25 21:29:47 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


int	main(int argc, char *argv[], char *envp[])
{
	t_data *data;
	char	*buffer;
	
	data->running = true;

	while (data->running)
	{
		write(1, "minishell-> ", 13);
		data->line = get_next_line(0);
	}
	
	return 0;
}
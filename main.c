/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/28 17:00:35 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_hostname(t_data *data)
{
	int	fd;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	if (fd == -1)
		return (-1);
	data->hostname = get_next_line(fd);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data data;
	char *buffer;

	data.running = true;
	if(get_hostname(&data)!= 0)
		return(ft_putstr("Error on hostname"),-1);
	while (data.running)
	{
		ft_putstr(data.hostname);
		// write(1, "minishell-> ", 13);
		data.line = get_next_line(0);
	}

	return (0);
}
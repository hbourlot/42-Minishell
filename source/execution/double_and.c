/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 18:05:52 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/27 16:26:02 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_double_and(t_shell *data, t_cmd *command)
{
	if (do_fork(&data->pid))
		return (-1);
	else if (data->pid == 0)
	{
		child_process(data, command, data->pipe_id, &data->prev_fd);
	}
	
}

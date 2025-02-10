/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:21:47 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/09 21:17:50 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// idx : 6
int	allocate_error(t_shell *data, const char *msg, char *insert)
{
	if (!ft_append_and_free(data->error_output, msg)
		|| !insert_string(data->error_output, ))
}

int	save_error_information(t_shell *data, t_cmd *command)
{
	const char *msg;
	
	if (command->settings.only_tokens)
	{
		msg = validate_command_path_access(command->rf);
		if (msg)
		{
			allocate_error(data, msg, )
		}
		//! error code == 1
	}
}


void set_error_child(int code, char *msg, const char *folder, bool exit)
{
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:56:28 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/26 20:12:30 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int initialize_cmds(t_cmd *command, char *cmd_line)
{
    char **cmds_split;
    int     i;
    
    cmds_split = ft_split(cmd_line, '|');
    if (!cmds_split)
        return (-1);
    while (command)
    {
        command->pre_command = cmds_split[i++];
        command = command->next;
    }
}
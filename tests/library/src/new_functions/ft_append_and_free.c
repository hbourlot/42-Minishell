/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_and_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:12:38 by hbourlot          #+#    #+#             */
/*   Updated: 2024/10/26 10:11:20 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD:source/process/execute_cmds.c
#include "minishell.h"

int	execute_commands(t_cmd *cmd)
{
}

int	execute(t_shell *data)
=======
#include "libft.h"

char	*ft_append_and_free(char *s1, char *s2)
>>>>>>> 163381ff135030ec3b4538fa728c4ead98330ae3:tests/library/src/new_functions/ft_append_and_free.c
{
	char	*result;
	int		i;
<<<<<<< HEAD:source/process/execute_cmds.c
	int		status;
	int		wait_status;
	pid_t	prev_pid;

=======
	int		j;

	if (!s1 && !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
>>>>>>> 163381ff135030ec3b4538fa728c4ead98330ae3:tests/library/src/new_functions/ft_append_and_free.c
	i = 0;
	while (s1 && s1[i])
	{
<<<<<<< HEAD:source/process/execute_cmds.c
		data->pid = waitpid(-1, &wait_status, 0);
		if (WIFEXITED(wait_status) && data->pid > prev_pid)
			status = WEXITSTATUS(wait_status);
		prev_pid = data->pid;
=======
		result[i] = s1[i];
>>>>>>> 163381ff135030ec3b4538fa728c4ead98330ae3:tests/library/src/new_functions/ft_append_and_free.c
		i++;
	}
	free(s1);
	j = 0;
	while (s2 && s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

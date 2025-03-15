/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:37:45 by hbourlot          #+#    #+#             */
/*   Updated: 2025/03/05 17:56:08 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_fail(t_shell *data, t_file *current)
{
	get_error_context()->exit = true;
	ft_printf_fd(2, "\nbash: warning: here-document at line ");
	ft_printf_fd(2, "%d delimited by end-of-file (wanted `%s')\n",
		data->nbr_of_lines, current->read);
}

static void	expand_in_pipe(t_file *current, char **text)
{
	char	*expanded;

	if (!current->in_quotes)
	{
		expanded = expand_command_input(*text, NULL);
		free(*text);
		*text = expanded;
	}
}

int	here_doc(int *pipe_id, t_file *current)
{
	char	*text;

	while (true)
	{
		text = readline("> ");
		if (!text)
			return (-1);
		if (ft_strlen(text) == 0)
		{
			free(text);
			continue ;
		}
		if (!ft_strcmp(current->read, text))
			return (free(text), 0);
		expand_in_pipe(current, &text);
		ft_printf_fd(pipe_id[1], "%s\n", text);
		free(text);
	}
	return (0);
}

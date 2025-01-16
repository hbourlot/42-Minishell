/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:31:14 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/16 11:37:31 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_file(int mode, char *file_name, t_file **file_list, t_token redirect)
{
	t_file	*current;
	t_file	*new_file;

	if (!file_list || !file_name || !*file_name)
		return (ERROR);
	new_file = ft_calloc(1, sizeof(t_file));
	if (!new_file)
		return (-1);
	if (mode == READ)
		new_file->read = file_name;
	else if (mode == WRITE)
		new_file->write = file_name;
	new_file->redirect = redirect;
	if (!*file_list)
		*file_list = new_file;
	else
	{
		current = *file_list;
		while (current->next)
			current = current->next;
		current->next = new_file;
	}
	return (SUCCESS);
}

static char	*get_file_name(char *src, const char *redirects[])
{
	int	i;

	i = 0;
	while (src && *src)
	{
		while (*src && *src == ' ' || ft_strcmps(&src[i], redirects) == CMP_OK)
			src++;
		while (src[i] && src[i] != ' ' && ft_strcmps(&src[i], redirects) < 0)
			i++;
		return (ft_substr(src, 0, i));
	}
	return (NULL);
}

static int handle_file_redirection(t_file **file_list, char **input_tmp, const char *redirects[], int mode)
{
	t_token redirect;
	char		*file_name;

	if (mode == READ)
		redirect = REDIRECT_LEFT_SINGLE;
	else
		redirect = REDIRECT_RIGHT_SINGLE;
	(*input_tmp)++;
	if (mode == READ && **input_tmp == '<')
		redirect = REDIRECT_LEFT_DOUBLE;
	else if (mode == WRITE && **input_tmp == '>')
		redirect = REDIRECT_RIGHT_DOUBLE;
	file_name = get_file_name(*input_tmp, redirects);
	if (!file_name || add_file(mode, file_name, file_list, redirect) == ERROR)
	{
		if (file_name)
			free(file_name);
		set_error_initialize(1, "Malloc", __func__, true);
		return (ERROR);
	}
	return (SUCCESS);
}

int	initialize_file_list(char *input, const char *redirects[], t_file **redir_files)
{
	char 			*file_name;
	char			*input_tmp;
	t_token 	redirect;

	input_tmp = input;
	while (input_tmp && *input_tmp)
	{
		if (*input_tmp == '>' && handle_file_redirection(redir_files, &input_tmp, redirects, WRITE) == ERROR)
			return (ERROR);
		else if (*input_tmp == '<' && handle_file_redirection(redir_files, &input_tmp, redirects, READ) == ERROR)
			return (ERROR);
		input_tmp++;
	}
	return (SUCCESS);
}

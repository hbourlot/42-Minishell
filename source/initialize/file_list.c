/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:31:14 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/07 15:08:02 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_file(char *input, int *position, t_token token,
		t_file **redir_files)
{
	t_file	*new;
	t_file	*current;
	char	*src;

	new = ft_calloc(1, sizeof(t_file));
	if (!new)
		return (-1);
	src = ft_substr(input, position[0], position[1] - position[0]);
	if (!src)
		return (-1);
	new->redirect = token;
	if (token == REDIRECT_LEFT_SINGLE)
		new->read = src;
	else if (token == REDIRECT_RIGHT_SINGLE || token == REDIRECT_RIGHT_DOUBLE)
		new->write = src;
	current = *redir_files;
	if (!current)
		*redir_files = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (0);
}

int	initialize_file_list(char *input, const char *redirects[],
		t_file **redir_files)
{
	int		idx;
	int		position[2];
	t_token	token;
	bool	in_quotes;

	in_quotes = false;
	while (input && *input)
	{
		if (*input && (*input == REP_DOUBLE_QUOTE
				|| *input == REP_SINGLE_QUOTE))
			in_quotes = !in_quotes;
		else if (!in_quotes && find_string_match(input, redirects, &idx) == OK)
		{
			token = get_t_token(input, ft_strlen(redirects[idx]));
			get_redirect_complement(input, &position[0], &position[1],
				ft_strlen(redirects[idx]));
			if (add_file(input, position, token, redir_files) < 0)
				return (-1);
		}
		input++;
	}
	return (0);
}









// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   file_list.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/24 15:31:14 by hbourlot          #+#    #+#             */
// /*   Updated: 2025/02/07 11:52:19 by hbourlot         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// static int	add_file(char *input, int *position, t_token token,
// 		t_file **redir_files)
// {
// 	t_file	*new;
// 	t_file	*current;
// 	char	*src;

// 	new = ft_calloc(1, sizeof(t_file));
// 	if (!new)
// 		return (-1);
// 	src = ft_substr(input, position[0], position[1] - position[0]);
// 	if (!src)
// 		return (-1);
// 	new->redirect = token;
// 	if (token == REDIRECT_LEFT_SINGLE)
// 		new->read = src;
// 	else if (token == REDIRECT_RIGHT_SINGLE || token == REDIRECT_RIGHT_DOUBLE)
// 		new->write = src;
// 	current = *redir_files;
// 	if (!current)
// 		*redir_files = new;
// 	else
// 	{
// 		while (current->next)
// 			current = current->next;
// 		current->next = new;
// 	}
// 	return (0);
// }

// 	// int		i;
// 	// bool	in_quotes;

// 	// i = 0;
// 	// in_quotes = false;
// 	// while (arg && arg[i])
// 	// {
// 	// 	// if ((arg[i] == REP_DOUBLE_QUOTE || arg[i] == REP_SINGLE_QUOTE))
// 	// 	// 	in_quotes = !in_quotes;
// 	// 	else if (!in_quotes && find_string_match(input, redirects, &idx) == OK)
// 	// 	{
// 	// 		token = get_t_token(input, ft_strlen(redirects[idx]));
// 	// 		get_redirect_complement(input, &position[0], &position[1],
// 	// 			ft_strlen(redirects[idx]));
// 	// 		if (add_file(input, position, token, redir_files) < 0)
// 	// 			return (-1);
// 	// 	}
// 	// }

// void	clean_args(char **args, int i)
// {
// 	int	j;

// 	free_pointers(2, &args[i], &args[i + 1])
// 	j = i + 2;
// 	while (args[j])
// 	{
// 		args[i] = args[j];
// 		i++;
// 		j++;
// 	}
// }
// int	iter_args(t_cmd *command, char *redirect_found, int i)
// {
// 	t_token token_id;
// 	int		len;
// 	int		j;
// 	int		p[2];

// 	j = 0;
// 	len = ft_strlen(redirect_found);
// 	token_id = get_t_token(redirect_found, len);
// 	while (command->args[i + 1][j])
// 	{
// 		if (command->args[i + 1][j] == REP_DOUBLE_QUOTE || command->args[i + 1][j] == REP_SINGLE_QUOTE)
// 			j++;
// 		p[0] = j;
// 		while (command->args[i + 1][j] && (command->args[i + 1][j] != REP_DOUBLE_QUOTE || command->args[i + 1][j] != REP_SINGLE_QUOTE))
// 			j++;
// 		p[1] = j;
// 		if (add_file(command->args[i + 1], p, token_id, &command->redir_files) < 0)
// 			return -1;
// 		else
// 			clean_args(command->args, i);
// 	}
// 	return 0;
// }

// int	verify_empty_complement(t_cmd *command, const char *redirects[], int i)
// {
// 	if (command->args[i + 1][0] == REP_DOUBLE_QUOTE || command->args[i + 1][0] == REP_SINGLE_QUOTE
// 	&& ft_strlen(command->args[i + 1]) == 2)
// 	{
// 		clean_args(command->args, i);
// 		command->args[i] = ft_strdup("");
// 		if (!command->args[i])
// 			return -1;
// 	}
// 	return 0;
// }
// int	initialize_file_list(t_cmd *command, const char *redirects[])
// {
// 	int		i;
// 	int		idx;
// 	int		position[2];
// 	t_token	token;

// 	i = 0;
// 	while (command->args && command->args[i])
// 	{
// 		if ((command->args[i][0] == REP_DOUBLE_QUOTE || command->args[i][0] == REP_SINGLE_QUOTE))
// 			continue;
// 		else if (find_string_match(command->args[i], redirects, &idx) == OK)
// 		{
// 			if (verify_empty_complement(command, redirects))
// 			if (iter_args(command, redirects[idx], i))
// 				return -1;	
// 		}
// 		i++;
// 	}
// 	return (0);
// }
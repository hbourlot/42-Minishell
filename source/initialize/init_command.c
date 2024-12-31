/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/26 22:36:37 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_cmd_list_on_error(t_cmd *cmd)
// ! Need manage this function in name and place to keep it
{
	t_cmd *tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	return (NULL);
}

t_cmd	*create_cmd(char *command_input, char *envp[])
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, sizeof(t_cmd));
	tmp->command_input = command_input;
	tmp->args = get_command_args(command_input);
	if (!tmp->args)
		printf("Error\n");
	tmp->envp = envp;
	return (tmp);
}

int	parse_input(t_shell *data, char *input, const char *delimiters[])
{
	data->input_splitted = split_by_multiple_tokens(input, delimiters);
	if (!data->input_splitted)
		return (-1);
	return (0);
}

static int	create_command_list(t_shell *data)
{
	t_cmd	*current;
	int		i;

	i = 0;
	data->command = create_cmd(data->input_splitted[i++], data->envp);
	if (!data->command)
		return (free(data->input_splitted), -1);
	current = data->command;
	while (data->input_splitted[i])
	{
		current->next = create_cmd(data->input_splitted[i++], data->envp);
		if (!current->next)
		{
			free_cmd_list_on_error(data->command);
			return (free_split(data->input_splitted), -1);
		}
		current = current->next;
	}
	data->nbr_of_commands = i;
	return (0);
}

int	init_command(char *input, const char *delimiters[])
{
	t_shell	*data;

	data = get_shell();
	if (parse_input(data, input, delimiters) < 0)
		return (-1); // Error in parsing input
	if (create_command_list(data) < 0)
		return (-1); // Error in creating command list
	return (0);
}

// int	init_command(char *input, const char *delimiters[])
// {
// 	t_cmd	*cmd;
// 	t_cmd	*current;
// 	char	**split_input;
// 	int		i;

// 	i = 0;
// 	split_input = split_by_multiple_tokens(input, delimiters);
// 	if (!split_input)
// 		return (-1); // ! Error managing here
// 	cmd = create_cmd(split_input[i++], get_shell()->envp);
// 	if (!cmd)
// 		return (free(split_input), -1);
// 	get_shell()->command = cmd;
//     get_shell()->input_splitted = split_input;
// 	current = cmd;
// 	while (split_input[i])
// 	{
// 		current->next = create_cmd(split_input[i++], get_shell()->envp);
// 		if (!current->next)
// 		{
// 			free_cmd_list_on_error(cmd);
// 			return (free_split(split_input), -1);
// ! Also need to free all previously struct command;
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }
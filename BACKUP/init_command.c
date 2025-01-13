/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/11 16:23:41 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char **extract_file_list(char *input, const char *redirects[])
{
	char 	**input_splitted;
	int		i;
	int		j;

	input_splitted = split_by_multiple_tokens(input, redirects);
	if (!input_splitted)
		return (NULL);
	free(input_splitted[0]);
	i = 1;
	j = 0;
	while (input_splitted[i])
	{
		input_splitted[j] = input_splitted[i];
		i++;
		j++;
	}
	input_splitted[j] = NULL;
	return (input_splitted);
}

static t_cmd	*add_command(char *input, char *envp[], char **env_paths, const char *redirects[])
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	ft_memset(command, 0, sizeof(t_cmd));
	command->input = input;
	command->envp = envp;
    command->path = get_path(input, env_paths);
    command->args = process_command_input(input);
    // command->file_list = extract_file_list(input, redirects);
    // command->settings.redir_count = 
    command->in_fd = -1;
    command->out_fd = -1;
	return (command);
}

static int parsing_command_input(t_shell *data, char *input, const char *delimiters[])
{
    int i;
    // char    **splitted;

    i = 0;
    // splitted = split_by_multiple_tokens();
    data->input_splitted = split_by_multiple_tokens(input, delimiters);
    if (!data->input_splitted)
        return (-1);
    // while (data->input_splitted[i])
    return (0);
}

static int create_command_list(t_shell *data, const char *redirects[])
{
    t_cmd   *current;
    int     i;

	i = 0;
    data->command = add_command(data->input_splitted[i++], data->envp, data->env_paths, redirects);
    if (!data->command)
        return (free(data->input_splitted), -1);
    current = data->command;
    while (data->input_splitted[i])
    {
        current->next = add_command(data->input_splitted[i++], data->envp, data->env_paths, redirects);
        if (!current->next)
        {
            // free_cmd_list_on_error(data->command);
            return (/* free_split(data->input_splitted), */ -1);
        }
        current = current->next;
    }
	data->nbr_of_commands = i;
    return (0);
}



int init_command(char *input)
{
    const char *redirects[] = {">", ">>", "<", "<<", NULL};
	const char *delimiters[] = {"|", "||", "&&", "&", NULL};
     
    t_shell *data;
	data = get_shell();
    if (parsing_command_input(data, input, delimiters) < 0)
        return (-1); // Error in parsing input
    if (create_command_list(data, redirects) < 0)
        return (-1); // Error in creating command list
    // cleanup_shell(data);
    // exit(0);
    // if (set_redirect(data->command))
    return (0);
}

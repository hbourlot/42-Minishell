/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:05:21 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/16 12:10:20 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// static void *free_cmd_list_on_error(t_cmd *cmd) // ! Need manage this function in name and place to keep it
// {
// 	t_cmd *tmp;

// 	tmp = cmd;
// 	while (cmd)
// 	{
// 		tmp = cmd;
// 		cmd = cmd->next;
// 		free(tmp);
// 	}
// 	return (NULL);
// }

static t_cmd	*add_command(char *input, char *envp[], char **env_paths)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	ft_memset(command, 0, sizeof(t_cmd));
	command->input = input;
	command->envp = envp;
    command->path = get_path(input, env_paths);
    command->args = get_command_args(input);
    command->in_fd = -1;
    command->out_fd = -1;
	return (command);
}

static int parse_input(t_shell *data, char *input, const char *delimiters[])
{
    data->input_splitted = split_by_multiple_tokens(input, delimiters);
    if (!data->input_splitted)
        return (-1);
    return (0);
}

static int create_command_list(t_shell *data)
{
    t_cmd   *current;
    int     i;

	i = 0;
    data->command = add_command(data->input_splitted[i++], data->envp, data->env_paths);
    if (!data->command)
        return (free(data->input_splitted), -1);
    current = data->command;
    while (data->input_splitted[i])
    {
        current->next = add_command(data->input_splitted[i++], data->envp, data->env_paths);
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

void    set_delimiters(t_cmd *command, char *input)
{
    const char  *delimiters[] = {"|", "||", "&", "&&", ">", ">>", "<", "<<", NULL};
    int         i;
    int         j;

    sort_strings_by_length_desc((char **)delimiters);
    j = 0;
    while (input[j])
    {
        i = 0;
        while (delimiters[i])
        {
            if (ft_strnstr(command->input, delimiters[i], ft_strlen(delimiters[i])) == CMP_OK)
            {
                printf("deli: %s\n", delimiters[i]);
                command->deli_test = (char *)delimiters[i];
                printf("command->deli_test: %s\n", command->deli_test);
                command = command->next;

            }
            i++;
        }
        j++;
    }
}


// int set_redirect(t_cmd *command)
// {
//     const char *redirects[] = {">", ">>", "<", "<<", NULL};
//     char        *command_input_splitted;
//     int         i;
    
//     while (command)
//     {
//         i = 0;
//         while (redirects[i])
//         {
//             if (ft_strnstr(command->input, redirects[i], ft_strlen(redirects[i])))
//             {
                
//             }

//         }
//     }
// }


int init_command(char *input, const char *delimiters[])
{
    t_shell *data;
	data = get_shell();
    if (parse_input(data, input, delimiters) < 0)
        return (-1); // Error in parsing input
    if (create_command_list(data) < 0)
        return (-1); // Error in creating command list
	set_delimiters(data->command, input);
    // while (data->command)
    // {
    //     printf("%s\n", data->command->deli_test);
    //     data->command = data->command->next;
    // }
    exit(0);
    // if (set_redirect(data->command))
    return (0);
}

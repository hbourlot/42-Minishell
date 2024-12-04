/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/04 18:46:09 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *find_first_delimiter(char *input, const char *delimiters[])
{
	int		j;
	char 	*occurrence;
	char 	*first_occur;
	char 	*tmp;
	
	occurrence = NULL;
	first_occur = NULL;
	j = 0;
	while (delimiters[j])
	{
		occurrence = ft_strstr(input, delimiters[j]);
		if (!first_occur)
			first_occur = occurrence;
		else if (occurrence && (occurrence <= first_occur))
			first_occur = occurrence;
		j++;
	}
	return (first_occur);
}
int get_delimiter_size(char *src, const char **to_find)
{
	int i;
	int	to_find_size;
	int	size;
	
	i = 0;
	size = 0;
	while (src && to_find[i])
	{
		to_find_size = ft_strlen(to_find[i]);
		if (!ft_strncmp(to_find[i], src, to_find_size))
			if (is_greater(to_find_size, size))
				size = ft_strlen(to_find[i]);
		i++;
	}
	return (size);
}

int get_nbr_of_commands(char *input, const char *delimiters[])
{
	int 		i;
	int			deli;

	i = 0;
	while (input)
	{
		input = find_first_delimiter(input, delimiters);
		deli = get_delimiter_size(input, delimiters);
		if (deli)
		{
			input += deli;
			i++;
		}
	}
	return (i);
}

static int match_delimiter(char *input, const char *delimiters[], int first_match)
{
    int i = 0;
	if (first_match != -1)
	{
		while (*input && *input == ' ')
			input++;
	}
    while (delimiters[i])
    {
        if (!ft_strncmp(input, delimiters[i], ft_strlen(delimiters[i])))
            return i;
		i++;
    }
    return -1;
}

bool is_delimiters_together(char *input, const char *delimiters[])
{
	int	first_match;
	int	second_match;

	first_match = -1;
    if (!input || !*input)
        return false;
    first_match = match_delimiter(input, delimiters, first_match);
    if (first_match != -1)
    {
        input += ft_strlen(delimiters[first_match]); 
        second_match = match_delimiter(input, delimiters, first_match);
        if (second_match != -1 && second_match != first_match)
            return true;
        return is_delimiters_together(input, delimiters);
    }
    return is_delimiters_together(input + 1, delimiters);
}

/*
	I'd probably add all parsing functions in this parsing_input function
*/
int	parsing_input(char *input, const char **delimiters)
{
	if (is_delimiters_together(input, delimiters))
	{
		printf("is_together\n");
		return (-1);
	}
	return (0);

}


char 	*filter_input(char *input, const char *delimiters[])
{
	int	i;
	int	j;
	int	deli_size;

	i = 0;
	while (input[i])
	{
		j = -1;
		while (delimiters[++j])
		{
			deli_size = ft_strlen(delimiters[j]);
			if (!ft_strncmp(&input[i], delimiters[j], deli_size))
			{
				printf("here\n");
				// memset(&input[i], 0, deli_size);
				input += (i + deli_size);
				printf("input: %s\n", input);
				return (input);
			}
			
		}
		i++;
	}
	return (NULL);
}


int	create_commands(char *input, const char *delimiters[])
{
	t_cmd	*cmd;

	cmd = get_shell()->command;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (-1); //! Error managing here
	cmd->command_input = input;
	input = filter_input(input, delimiters);
	// while (input)
	// {
	// 	cmd->next = malloc(sizeof(t_cmd));
	// 	if (!cmd->next)
	// 		return (-1); //! Error managing here
	// 	cmd = cmd->next;
	// 	cmd->command_input = input;
	// 	input = filter_input(input, delimiters);
	// }
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;
	char 		*input;
	const char *delimiters[] = {"||", "&&", "|", NULL};

	get_shell();
	input = "echo 'test' |  a   la vai ";
	if (parsing_input(input, delimiters))
		return (error_msg(), 1);	
	if (create_commands(input, delimiters))
		printf("error no create\n");
	debug_command_input(get_shell());
	// data = get_shell();
	// if (init_program(data))
	// 	return (1); // ! Error managing here
	// cleanup_shell(data);
	return 0;
}













	// char *test[] = {"echo", "$PATH", NULL};
	// execve("/bin/echo", test, NULL);


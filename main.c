/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/03 13:08:35 by hbourlot         ###   ########.fr       */
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

bool	is_delimiters_together(char *input, const char *delimiters[])
{
	int	i;
	int	j;
	int	k;
	
	i = -1;
	while (delimiters[++i])
	{
		j = -1;
		while (input)
		{
			if (input && *input == ' ')
				continue;
			if (!ft_strncmp(input, delimiters[i], ft_strlen(delimiters[i])))
			{
				k = -1;
				while (delimiters[++k])
				{
					if (k == i)
						continue;
					if (!ft_strncmp(input + ft_strlen(delimiters[i]), delimiters[k], ft_strlen(delimiters[k])))
						return (true);
				}
			}
			input++;
		}
	}
	return (false);
}

// bool	is_next_delimiter_separate(char *input, const char *delimiters[], int deli_to_skip)
// {
// 	int k;
// 	int	i;

// 	i = -1;
// 	k = -1;
// 	while (input[++i])
// 	{
// 		while (delimiters[++k])
// 		{
// 			if (k == deli_to_skip)
// 				continue;
// 			if (!ft_strncmp(input + ft_strlen(delimi)))
// 		}
		
// 	}
// }

bool	is_delimiters_together(char *input, const char *delimiters[])
{
	int	j;
	int	k;
	// bool	first_delimiter;
	// bool	second_delimiter;
	
	// if (input && *input == ' ')
	// 	continue;
	while (input && *input++)
	{
		j = -1;
		while (delimiters[++j])
		{
			if (!ft_strncmp(input, delimiters[j], ft_strlen(delimiters[j])))
			{
				
				is_delimiters_together(input + ft_strlen(delimiters[j]), delimiters);
				// k = -1;
				// while (delimiters[++k])
				// {
				// 	if (k == j)
				// 		continue;
				// 	if (!ft_strncmp(input + ft_strlen(delimiters[i]), delimiters[k], ft_strlen(delimiters[k])))
				// 		return (true);
				// }
			}
			input++;
		}
	}
	return (false);
}

// t_cmd *init_command(char *input, const char *delimiters[])
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->command_input = find_first_delimiter(input, delimiters);
// 	if (!cmd->command_input)
// 		return (free(cmd), NULL);
	
// }

// t_cmd *create_command_list(char *input, const char *delimiters[])
// {
// 	int	nbr_of_cmds;
// 	t_cmd	*head;
// 	t_cmd	*tmp;
	
// 	head = malloc(sizeof(head));
// 	if (!head)
// 		return (NULL);
// 	head->command_input = find_first_delimiter(input, delimiters);
// 	nbr_of_cmds = get_nbr_of_cmds(input, delimiters);
// 	tmp = head;
	
// 	while (nbr_of_cmds--)
// 	{
// 		tmp->next = malloc()	
// 	}
// }


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

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;
	char 		*input;
	const char *delimiters[] = {"||", "&&", "|", NULL};


	input = "echo 'test' |     ||  la vai ";
	// printf("%s\n", find_first_delimiter(input, delimiters));
	if (parsing_input(input, delimiters))
		return (error_msg(), 1);	
	
	// data = get_shell();
	// if (init_program(data))
	// 	return (1); // ! Error managing here
	// cleanup_shell(data);
	return 0;
}


	// char *test[] = {"echo", "$PATH", NULL};
	// execve("/bin/echo", test, NULL);


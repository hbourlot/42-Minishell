/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/02 09:28:40 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


char *find_first_delimiter(char *input, const char **delimiters)
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

int nbr_of_commands(char *input, const char **to_find)
{
	int 		i;
	int			deli;

	i = 0;
	while (input)
	{
		input = find_first_delimiter(input, to_find);
		deli = get_delimiter_size(input, to_find);
		if (deli)
		{
			input += deli;
			i++;
		}
	}
	return (i);
}

bool	is_delimiters_together(char *input, const char **delimiters)
{
	int	i;
	int	j;
	int	k;
	
	i = -1;
	while (delimiters[++i])
	{
		j = -1;
		while (input[++j])
		{
			if (!ft_strncmp(input + j, delimiters[i], ft_strlen(delimiters[i])))
			{
				k = -1;
				while (delimiters[++k])
				{
					if (k == i)
						continue;
					if (!ft_strncmp(input + j + ft_strlen(delimiters[i]), delimiters[k], ft_strlen(delimiters[k])))
						return (true);
				}
			}	
		}
	}
	return (false);
}

int	main(int argc, char *argv[], char *envp[])
{
	// t_shell		*data;
	char 		*input;

	const char *to_find[] = {"|", "||", "&&", NULL};
	char *ex = "|echo 'test'  | ||  la vai ||&&";
	if (is_delimiters_together(ex, to_find))
		printf("together\n");
	else
	{
		printf("separate\n");

	}
	
	// int	nbr = get_nbr_of_commands(ex, to_find);
	// printf("nbr: %d\n", nbr);
	// printf("ex: %s\n", ex);
	// char *f1 = find_first_delimiter(ex, to_find);
	

	// data = get_shell();
	// if (init_program(data))
	// 	return (1); // ! Error managing here
	// cleanup_shell(data);
	return 0;
}


	// char *test[] = {"echo", "$PATH", NULL};
	// execve("/bin/echo", test, NULL);


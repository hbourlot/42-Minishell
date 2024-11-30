/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:19 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/30 17:28:09 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


char *find_first_occurrence(char *src, const char **to_find)
{
	int		j;
	char 	*occurrence;
	char 	*first_occur;
	
	occurrence = NULL;
	first_occur = NULL;
	j = 0;
	while (to_find[j])
	{
		occurrence = ft_strstr(src, to_find[j]);
		printf("ocurrence: %s\n", occurrence);
		if (!first_occur)
			first_occur = occurrence;
		if (occurrence && (occurrence <= first_occur))
		{
			first_occur = occurrence;
			printf("first_occur: %s\n", first_occur);
		}
		j++;
	}
	printf("first_occur(out): %s\n", first_occur);
	return (first_occur);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*data;
	char 		*input;

	const char *to_find[] = {"|", "||", "&&"};
	
	printf("%s\n", find_first_occurrence("echo 'test' | la vai ||", to_find));


	// data = get_shell();
	// if (init_program(data))
	// 	return (1); // ! Error managing here
	// cleanup_shell(data);
	return 0;
}


	// char *test[] = {"echo", "$PATH", NULL};
	// execve("/bin/echo", test, NULL);

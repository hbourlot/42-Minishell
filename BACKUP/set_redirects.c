/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:17:21 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/18 19:17:22 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	count_redirects(char *input, const char *redirects[])
{
	int i;
	int	j;
	int	tot;

	i = -1;
	tot = 0;
	sort_strings_by_length_desc(redirects);
	while (input[++i])
	{
		j = -1;
		while (redirects[++j])
		{
			if (ft_strncmp(&input[i], redirects[j], ft_strlen(redirects[j])) == CMP_OK)
				tot++;
		}
	}
	return (tot);
}

char **grep_file(char *input, const char *redirects[])
{
	char 	**input_splitted;
	int		i;
	int		j;

	input_splitted = split_by_multiple_tokens(input, redirects);
	if (!input_splitted)
		return (NULL);
	free(input_splitted[0]);
	i = 0;
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



/* 
	* echo oi>test>oi oi oi
*/
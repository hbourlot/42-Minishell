/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_command_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:27:32 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/30 11:25:50 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	find_matching_character(int *first, int *second, char *src, int character)
{
	int	i;

	i = 0;
	*first = -1;
	*second = -1;
	while (src[i])
	{
		if (src[i] == character && *first == -1)
			*first = src[i];		
		else if (src[i] == character && *second == -1)
			*second = src[i];
		i++;
	}
	if (*first != -1 && *second != -1)
		return (1);
	return (0);
}

int	count_char_occurrences(char *src, int character)
{
	int i;
	int nbr;

	nbr = 0;
	i = 0;
	if (!src || !*src)
		return (-1);
	while (src[i])
	{
		if (src[i] == character)
			nbr++;
		i++;
	}
	return (nbr);
}

void	token_init(char *pre_command, t_token *token)
{
	int	nbr_occurrences;
	char *last_occurrence;
	
	last_occurrence = NULL;
	nbr_occurrences = count_char_occurrences(pre_command, '\'');
	if (nbr_occurrences && nbr_occurrences % 2)
	{
		token->here_doc = true;
		token->last_occurrence = ft_strrchr(pre_command, "'");
	}

}
// * Basically the command might be the start of pre_command until
// * 	the byte before the last_occurrence.



int	parsing_input(char *input, char *token)
{
	int	i;

	while (input[i])	
}
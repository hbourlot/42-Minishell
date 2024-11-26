/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/26 20:08:12 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "../lib/library/inc/libft.h"


// -- TOKENS
#define START_OF_TEXT	02
#define END_OF_TEXT		03

typedef struct s_cmd_tokens
{
	int			nbr_of_cmds;

} 				t_cmd_tokens;

typedef struct s_cmd
{
	char					*pre_command;
	int						out_fd;
	int						in_fd;
	char					**args;
	char					*path;
	char					**envp;
	struct s_cmd_tokens 	tokens;
	struct s_cmd			*next;
}					t_cmd;

typedef struct s_data
{
	char			**cmds_splitted;
	struct t_cmd	*command;
} 	t_shell;

char	**get_args(char *argv);


#endif
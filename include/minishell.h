/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2024/11/29 15:30:20 by hbourlot         ###   ########.fr       */
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
# include <readline/history.h>
# include "../lib/library/inc/libft.h"

// -- TOKENS
#define START_OF_TEXT	02
#define END_OF_TEXT		03

typedef struct s_cmd_tokens
{
	bool			here_doc;
	char			*last_occurrence;
	char 			*pre_command;
	
} 				t_token;

typedef struct s_cmd
{
	char					*pre_command;
	int						out_fd;
	int						in_fd;
	char					**args;
	char					*path;
	char					**envp;
	struct s_cmd_tokens 	token;
	struct s_cmd			*next;
}					t_cmd;

typedef struct s_data
{
	char			**input_splitted;
	struct s_cmd	*command;
} 	t_shell;


// ************************************************************************
// **						Create Functions							 **
// ************************************************************************

t_cmd		*create_command_list(char **input_splitted);

// ************************************************************************
// **						Initialize Functions						 **
// ************************************************************************

t_shell 	*get_shell();
int			init_program(t_shell *data);
int			initialize_command(char **input_splitted, t_cmd *command);

// ************************************************************************
// **						Proccess Functions						 	 **
// ************************************************************************

char		**get_command_args(char *argv);

// ************************************************************************
// **						Free Functions							 	 **
// ************************************************************************

void		cleanup_shell(t_shell*data);

// ************************************************************************
// **						Utils Functions							 	 **
// ************************************************************************

void		debug_command_precommand(t_shell *data);
void		debug_command_args(t_shell *data);

#endif
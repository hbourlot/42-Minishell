/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/01 14:13:43 by hbourlot         ###   ########.fr       */
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


typedef enum s_delimiter
{
	PIPE = 1,
	OR = 2,
	AND = 2,
} t_deli;



typedef struct s_rules
{	
	t_deli				delimiter_type;
	bool				here_doc;
	bool				or_next;
	bool				or_prev;
	char				*last_occurrence;
	char 				*pre_command;
	
} 				t_rules;

typedef struct s_cmd
{
	char					*pre_command;
	int						out_fd;
	int						in_fd;
	char					**args;
	char					*path;
	char					**envp;
	struct s_rules		 	settings;
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
int			initialize_command(char *input, t_cmd *command);

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
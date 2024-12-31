/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/26 22:36:37 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/library/inc/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// -- TOKENS
# define CMP_OK 0
# define CMP_ERROR 1
# define START_OF_TEXT 02
# define END_OF_TEXT 03

typedef enum s_delimiter
{
	PIPE = 1,
	OR = 2,
	AND = 2,
}					t_deli;

typedef struct s_rules
{
	t_deli			delimiter_type;
	bool			here_doc;
	bool			or_next;
	bool			or_prev;
	char			*last_occurrence;
	char			*pre_command;

}					t_rules;

typedef struct s_cmd
{
	char			*command_input;
	int				out_fd;
	int				in_fd;
	char			**args;
	char			*path;
	char			**envp;
	struct s_rules	settings;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			**input_splitted;
	int				nbr_of_commands;
	int				argc;
	char			**argv;
	char			**envp;
	pid_t			pid;
	struct s_cmd	*command;
}					t_shell;

// ************************************************************************
// **						Parsing Functions								**
// ************************************************************************
int					parsing_input(char *input, const char **delimiters);

// ************************************************************************
// **						Create Functions								**
// ************************************************************************

// t_cmd		*create_command_list(char **input_splitted);

// ************************************************************************
// **						Initialize Functions							**
// ************************************************************************

t_shell				*get_shell(void);
int					init_program(t_shell *data);
int					init_command(char *input, const char *delimiters[]);

// ************************************************************************
// **						Proccess Functions									**
// ************************************************************************

char				**get_command_args(char *argv);
char				*expand_var(char *str);
char				**get_command_args(char *input);

// ************************************************************************
// **						Free Functions										**
// ************************************************************************

void				cleanup_shell(t_shell *data);

// ************************************************************************
// **						Utils Functions										**
// ************************************************************************

void				debug_command_input(t_shell *data);
void				debug_command_args(t_shell *data);
void				error_msg(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/12 14:39:22 by hbourlot         ###   ########.fr       */
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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/library/inc/libft.h"


// ************************************************************************
// **						      MACROS  								 **
// ************************************************************************

#define READ  			0
#define WRITE 			1
#define	CMP_OK			0
#define CMP_ERROR		1
#define START_OF_TEXT	02
#define END_OF_TEXT		03
#define ABS_PATH 		"PATH=/bin:/usr/bin:/usr/local/bin"

// ************************************************************************
// **						     STRUCTURES  							 **
// ************************************************************************

typedef enum e_delimiter
{
	PIPE_SINGLE,          // single pipe `|`
	PIPE_DOUBLE,          // double pipe `||`
	AND_SINGLE,           // single AND `&`
	AND_DOUBLE,           // double AND `&&`
	REDIRECT_RIGHT_SINGLE, // single right redirection `>`
	REDIRECT_RIGHT_DOUBLE, // double right redirection `>>`
	REDIRECT_LEFT_SINGLE,  // single left redirection `<`
	REDIRECT_LEFT_DOUBLE   // double left redirection `<<`
}	t_delimiter;

typedef struct s_rules
{	
	bool				here_doc;
	bool				or_next;
	bool				or_prev;
	char				*last_occurrence;
	char 				*pre_command;
	
} 					t_rules;

typedef struct s_cmd
{
	t_delimiter			delimiter;
	char				*command_input;
	char				*file;
	int					out_fd;
	int					in_fd;
	char				**args;
	char				*path;
	char				**envp;
	struct s_rules		settings;
	struct s_cmd		*next;
}					t_cmd;

typedef struct s_data
{
	char			**input_splitted;
	char			**env_paths;
	int				nbr_of_commands;
	int				argc;
	char			**argv;
	char			**envp;
	pid_t			pid;
	struct s_cmd	*command;
} 					t_shell;


// ************************************************************************
// **						Parsing Functions							 **
// ************************************************************************

int			parsing_input(char *input, const char **delimiters);

// ************************************************************************
// **						Create Functions							 **
// ************************************************************************

// t_cmd		*create_command_list(char **input_splitted);

// ************************************************************************
// **						Initialize Functions						 **
// ************************************************************************

t_shell 	*get_shell();
t_shell		*init_shell(int argc, char *argv[], char *envp[]);
int			init_program(t_shell *data);
int			init_command(char *input, const char *delimiters[]);

// ************************************************************************
// **						Proccess Functions						 	 **
// ************************************************************************

char		**get_command_args(char *argv);
void		execution(t_shell *data);
char 		*get_path(char *command_input, char **env_paths);
int			open_folder(char *file, t_cmd *command, bool here_doc);
int			do_dup2(t_cmd *command, int *pipe_id, int *prev_fd);


// ************************************************************************
// **						Free Functions							 	 **
// ************************************************************************

void		cleanup_shell(t_shell*data);

// ************************************************************************
// **						Utils Functions							 	 **
// ************************************************************************

void		debug_command_input(t_shell *data);
void		debug_command_args(t_shell *data);
void		debug_command_path(t_shell *data);

void 		error_msg(void);

#endif

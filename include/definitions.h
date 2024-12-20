/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:07 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/20 21:39:30 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

#include "minishell.h"

// ************************************************************************
// **						      MACROS  								 **
// ************************************************************************

#define READ  				0
#define WRITE 				1
#define	CMP_OK				0
#define CMP_ERROR			1
#define START_OF_TEXT		02
#define END_OF_TEXT			03
#define ABS_PATH 			"PATH=/bin:/usr/bin:/usr/local/bin"
#define SYNTAX_ERROR_MSG 	"bash: syntax error near unexpected token `"

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

typedef struct s_error
{
	int		code;
	char	*token;
	char 	*message;
	char	*function;
}	t_error;


typedef struct s_rules
{	
	bool				here_doc;
	bool				or_next;
	bool				or_prev;
	int					redir_count;
	char				*last_occurrence;
	char 				*pre_command;
	
} 					t_rules;

typedef struct s_cmd
{
	t_delimiter			delimiter;
	// char				*deli_test;
	char				*input;
	// char				**file_list;
	char 				*file;
	char				**file_list[2];
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

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:07 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/28 17:38:47 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

#include "minishell.h"

// ************************************************************************
// **						      MACROS  								 **
// ************************************************************************

// File Descriptors
#define READ  				0
#define WRITE 				1

// Status Codes
#define	CMP_OK				0
#define CMP_ERROR			1
#define OK					0
#define ERROR				-1
#define SUCCESS				0

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

// typedef struct s_error
// {
// 	int		code;
// 	char	*token;
// 	char	*archive;
// 	char 	*message;
// 	char	*function;
// }	t_error;

typedef struct s_file
{
	char 			*read;
	char			*write;
	t_delimiter		redirect;
	struct s_file	*next;
}			t_file;


typedef struct s_rules
{	
	bool				here_doc;
	bool				or_next;
	bool				or_prev;
	// int					redir_count;
	bool				only_redir_files;
	char				*last_occurrence;
	char 				*pre_command;
	
} 					t_rules;

typedef struct s_cmd
{
	t_delimiter			delimiter;
	char				*input;
	char 				*file;
	t_file				*redir_files;
	int					in_fd;
	int					out_fd;
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
	int				last_exit_status;
	int				nbr_of_commands;
	int				argc;
	char			**argv;
	char			**envp;
	pid_t			pid;
	struct s_cmd	*command;
} 					t_shell;

#endif
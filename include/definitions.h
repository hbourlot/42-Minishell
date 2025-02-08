/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:07 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/08 15:55:29 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include "minishell.h"

// ***********************************************************************
// **								MACROS  							**
// ***********************************************************************

// sqpa_tokens: space and quotes and pipes and &&

// File Descriptors
# define READ 0
# define WRITE 1

// Status Codes
# define CMP_OK 0
# define CMP_ERROR 1
# define OK 0
# define ERROR -1
# define SUCCESS 0
# define NO_FILE_DIR 1
# define PERM_DENIED 1

// Representations
# define REP_SINGLE_QUOTE 1
# define REP_DOUBLE_QUOTE 2
# define REP_SPACE 3
# define REP_PIPE 4
# define REP_AND 5

# define ABS_PATH "PATH=/bin:/usr/bin:/usr/local/bin"
# define SYNTAX_ERROR_MSG "bash: syntax error near unexpected token `"
# define NO_FILE_DIR_MSG "No such file or directory"
# define PROMPT "\033[1;32m[Chitãozinho&Xororó\033[1;31m@localhost ~]$ \033[0m"

# define HASHMAP_SIZE 10

// ***************************************************************************
// **								STRUCTURES  							**
// ***************************************************************************

typedef enum e_token
{
	NO_TOKEN,
	PIPE_SINGLE,
	PIPE_DOUBLE,
	AND_DOUBLE,
	REDIRECT_RIGHT_SINGLE,
	REDIRECT_RIGHT_DOUBLE,
	REDIRECT_LEFT_SINGLE,
	REDIRECT_LEFT_DOUBLE
}						t_token;

typedef enum e_builtin
{
	CD = 1,
	EXPORT,
	ECHO,
	ENV,
	UNSET,
	EXIT,
	PWD
}						t_builtin;

typedef struct s_file
{
	char				*read;
	char				*write;
	t_token				redirect;
	struct s_file		*next;
}						t_file;

typedef struct s_rules
{
	char				**eof;
	bool				expansion;
	bool				only_tokens;
	bool				is_builtin;
	bool				is_safe_to_execve;
	bool				is_safe_to_builtin;
	t_builtin			builtin_id;
}						t_rules;

typedef struct s_cmd
{
	t_token				delimiter;
	t_file				*redir_files;
	t_rules				settings;
	bool				expansion;
	char				*input;
	char				*file;
	int					fd_in;
	int					fd_out;
	int					io[2];
	char				**args;
	char				*path;
	char				**envp;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_hashnode
{
	char				*key;
	char				*value;
	struct s_hashnode	*next;
}						t_hashnode;

typedef struct s_hashmap
{
	t_hashnode			*slots[HASHMAP_SIZE];
	size_t				total_size;
}						t_hashmap;

typedef struct s_data
{
	bool				it_ends_with_delimiter;
	// bool				its_only_eof;
	pid_t				pid;
	char				*error_output;
	int					pipe_id[2];
	int					prev_fd;
	char				*rl;
	char				**eof;
	char				**rl_splitted;
	char				**env_paths;
	int					exit_status;
	int					nbr_of_commands;
	int					nbr_of_lines;
	int					commands_ran;
	int					argc;
	char				**argv;
	char				**envp;
	t_cmd				*command;
	t_cmd				*last_cmd_executed;
	t_hashmap			*map;
}						t_shell;

typedef void			(*t_here_doc_handler)(t_shell *, t_cmd *);
typedef void			(*t_builtin_handler)(t_shell *, t_cmd *);
typedef void			(*t_command_executor)(t_shell *, t_cmd *);
typedef int				(*t_access_check_function)(const char *path);
typedef int				(*t_executer_handler)(t_shell *, t_cmd *);

#endif

// * [] it_ends_with_delimiter and it_ends_with_double_pipe
// * [X] exit_status prob is working

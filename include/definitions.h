/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:07 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/30 16:40:34 by hbourlot         ###   ########.fr       */
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
	PIPE_SINGLE,
	PIPE_DOUBLE,
	AND_DOUBLE,
	REDIRECT_RIGHT_SINGLE,
	REDIRECT_RIGHT_DOUBLE,
	REDIRECT_LEFT_SINGLE,
	REDIRECT_LEFT_DOUBLE
}						t_token;

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
	bool				or_next;
	bool				expansion;
	bool				only_tokens;
	bool				is_builtin;
	bool				builtin_cd;
	bool				builtin_echo;
	bool				builtin_env;
	bool				builtin_exit;
	bool				builtin_export;
	bool				builtin_unset;
	bool				builtin_pwd;
}						t_rules;

typedef struct s_cmd
{
	t_token				delimiter;
	t_file				*redir_files;
	t_rules				settings;
	char				*input;
	char				*file;
	int					fd_in;
	int					fd_out;
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
	bool				its_only_eof;
	// bool				it_ends_with_double_pipe;
	pid_t				pid;
	int					pipe_id[2];
	int					prev_fd;
	char				*readline;
	char				**eof;
	char				**readline_splitted;
	char				**env_paths;
	int					exit_status;
	int					nbr_of_commands;
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

#endif

// * [] it_ends_with_delimiter and it_ends_with_double_pipe
// * [X] exit_status prob is working

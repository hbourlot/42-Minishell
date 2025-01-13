/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/13 15:19:12 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include "../lib/library/inc/libft.h"
# include "definitions.h"
# include "error.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// ************************************************************************
// **						Parsing Functions								**
// ************************************************************************

int		parsing_syntax(char *input);
bool	is_valid_pipe_tokens(char *source);
void	identify_and_replace_sq_tokens(char **input);
bool	is_valid_file_and_here_doc_tokens(char *source);
int		parsing_file_read_execution(t_file *redir_files);
int		parsing_command_path_execution(char *command_path);
int		strip_redirects(char **input, const char *redirects[]);

// ************************************************************************
// **						Create Functions								**
// ************************************************************************

// t_cmd		*create_command_list(char **input_splitted);

// ************************************************************************
// **						Initialize Functions							**
// ************************************************************************

t_shell	*get_shell(void);
int		init_command(char *input);
int		main_shell_loop(t_shell *data);
int		initialize_environment_paths(t_shell *data);
t_shell	*init_shell(int argc, char *argv[], char *envp[]);
int		initialize_here_doc(char *input_splitted, char ***eof);
int		add_command(t_cmd **command, char *input_splitted, t_shell *data);
int		initialize_file_list(char *input, const char *redirects[],
			t_file **redir_files);

// ************************************************************************
// **						Execution Functions									**
// ************************************************************************

void	run_commands(t_shell *data);
char	**process_command_input(char *argv);
int		here_doc(int *pipe_id, char *limiter);
char	*get_path(char *input, char **env_paths);
int		do_dup2(t_cmd *command, int *pipe_id, int *prev_fd);
int		open_folder(char *file, t_cmd *command, bool here_doc);
int		run_eof(t_cmd *command, int *pipe_id, int *prev_fd, pid_t *pid);
int		open_folders_safety(int *fd_in, int *fd_out, t_file *redir_files);
char	*process_variables(char *str);
char	**tokenize_element(char *element);
char	**tokenize_bash_variables(char *src);

// ************************************************************************
// **						Free Functions										**
// ************************************************************************

void	cleanup_shell(t_shell *data);
void	free_files(t_file *file_list);
void	refresh_shell_data(t_shell *data);

// ************************************************************************
// **						Utils Functions										**
// ************************************************************************

void	skip_spaces(char **src);
void	debug_command_args(t_shell *data);
void	debug_command_path(t_shell *data);
void	skip_character(char **src, char c);
void	debug_command_input(t_shell *data);
void	debug_input_splitted(t_shell *data);
void	debug_command_file_list(t_shell *data);
void	skip_character_diff(char **src, char c);
void	print_execve_parameters(char *input);



// * Bad procesing

void	signal_handler(int signal);

#endif

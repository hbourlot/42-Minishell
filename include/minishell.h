/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/07 14:45:04 by hbourlot         ###   ########.fr       */
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
# include "error.h"
# include "definitions.h"

// ************************************************************************
// **						Parsing Functions							 **
// ************************************************************************

int			parsing_syntax(char *input);
bool 		is_valid_pipe_tokens(char *source);
bool 		is_valid_file_and_here_doc_tokens(char *source);
int			parsing_file_read_execution(t_file *redir_files);
int			parsing_command_path_execution(char *command_path);
int 		strip_redirects(char **input, const char *redirects[]);

// ************************************************************************
// **						Create Functions							 **
// ************************************************************************

// t_cmd		*create_command_list(char **input_splitted);

// ************************************************************************
// **						Initialize Functions						 **
// ************************************************************************

t_shell 	*get_shell();
int			init_command(char *input);
int			main_shell_loop(t_shell *data);
int			initialize_environment_paths(t_shell *data);
t_shell		*init_shell(int argc, char *argv[], char *envp[]);
int			initialize_here_doc(char *input_splitted, char ***eof);
int 		add_command(t_cmd **command, char *input_splitted, t_shell *data);
int 		initialize_file_list(char *input, const char *redirects[], t_file **redir_files);

// ************************************************************************
// **						Execution Functions						 	 **
// ************************************************************************

void		run_commands(t_shell *data);
char		**get_command_args(char *argv);
int			here_doc(int *pipe_id, char *limiter);
char 		*get_path(char *input, char **env_paths);
int			do_dup2(t_cmd *command, int *pipe_id, int *prev_fd);
int			open_folder(char *file, t_cmd *command, bool here_doc);
int			run_eof(t_cmd *command, int *pipe_id, int *prev_fd, pid_t *pid);
int			open_folders_safety(int *in_fd, int *out_fd, t_file *redir_files);

// ************************************************************************
// **						Free Functions							 	 **
// ************************************************************************

void		cleanup_shell(t_shell*data);
void 		free_files(t_file *file_list);
void		refresh_shell_data(t_shell *data);

// ************************************************************************
// **						Utils Functions							 	 **
// ************************************************************************

void 		skip_spaces(char **src);
void		debug_command_args(t_shell *data);
void		debug_command_path(t_shell *data);
void		debug_command_input(t_shell *data);
void 		debug_input_splitted(t_shell *data);
void 		debug_command_file_list(t_shell *data);
void		debug_readline_processed(t_shell *data);

#endif

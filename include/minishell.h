/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2025/01/30 15:40:53 by joralves         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// ************************************************************************
// **						Parsing Functions								**
// ************************************************************************

int			parsing_syntax(t_shell *data);
bool 		is_valid_pipe_tokens(char *source);
void		identify_and_replace_sqpa_tokens(char *input);
bool 		is_valid_file_and_here_doc_tokens(char *source);
int			validate_file_read_execution(t_file *redir_files);
int			validate_command_path_access(char *command_path);
// int 		strip_redirects(char **input, const char *redirects[]);
void		strip_redirects(char *input, const char *redirects[]);



// ************************************************************************
// **						Initialize Functions							**
// ************************************************************************

t_shell 	*get_shell();
int			init_command(t_shell *data);
int			main_shell_loop(t_shell *data);
bool		 is_quotes_maching(char *input);
char		**tokenize_element(char *element);
char		*process_variables(char *cmd_token);
char		**tokenize_bash_variables(char *src);
char		**process_command_input(char *input);
void		process_eof_truncation(t_shell *data);
int			initialize_environment_paths(t_shell *data);
t_shell		*init_shell(int argc, char *argv[], char *envp[]);
int			initialize_eof(char *data_readline, char ***data_eof);
int			add_command(t_cmd **command, char *readline_splitted, t_shell *data,
				t_token token_type);
int			initialize_file_list(char *input, const char *redirects[],
				t_file **redir_files);
t_hashmap	*create_map(void);
int			hashmap_insert(t_hashmap *map, char *key, char *value);
char		*hashmap_search(t_hashmap *map, char *key);
void		hashmap_delete(t_hashmap *map, char *key);
void		hashmap_display(t_hashmap *map);
void		hashmap_free(t_hashmap *map);
int			hashmap_to_env_array(t_shell *data, t_hashmap *map);
int			import_env_to_hashmap(t_hashmap *map, char *envp[]);
int			update_envp_and_envpath(t_shell *data);

// ************************************************************************
// **						Execution Functions								**
// ************************************************************************


int			print_command_on_terminal(t_shell *data, pid_t *pid);

// int			do_pipe(int *pipe_id);
int			do_fork(pid_t *pid);
void		run_commands(t_shell *data);
void		set_last_status(t_shell *data);
int			handle_double_pipe(t_shell *data);
int			here_doc(int *pipe_id, char *limiter);
char 		*get_path(char *input, char **env_paths);
void		command_loop(t_shell *data, t_cmd *command);
void		handle_double_and(t_shell *data, t_cmd *command);
int			open_folder(char *file, t_cmd *command, bool here_doc);
int			do_dup2(int *fd_in, int *fd_out, int *pipe_id, int *prev_fd);
int			run_eof(t_shell *data, int *pipe_id, int *prev_fd, pid_t *pid);
int			open_folders_safety(int *fd_in, int *fd_out, t_file *redir_files);
void		child_process(t_shell *data, t_cmd *command, int *pipe_id, int *prev_fd);
int			parent_process(t_shell *data, t_cmd *command);

// ************************************************************************
// **						Free Functions									**
// ************************************************************************

void		cleanup_shell(t_shell *data);
void		free_files(t_file *file_list);
void		refresh_shell_data(t_shell *data);

// ************************************************************************
// **						Utils Functions									**
// ************************************************************************

void		skip_spaces(char **src);
void		debug_command_args(t_shell *data);
void		debug_command_path(t_shell *data);
void		debug_command_input(t_shell *data);
void		debug_input_splitted(t_shell *data);
t_token		get_t_token(char *src, size_t size);

void 		debug_command_file_list(t_shell *data);
void		restore_original_characters(char **src);
void 		skip_character_by_idx(char *src, char c, int *i);
void		skip_character_diff_by_idx(char *src, char c, int *i);
void		replace_characters(char *src, char to_take, char to_put);
void		get_redirect_complement(char *src, int *start, int *end, int redirect_size);

// ************************************************************************
// **						BuiltIn											**
// ************************************************************************

void		builtin_pwd(t_shell *data);
void		set_builtin_flag(t_cmd *last_node);
void		builtin_exit(t_shell *data, t_cmd *cmd);
int			builtin_cd(t_shell *data, char **command_args);
void		builtin_env(t_shell *data, char **command_args);
void		builtin_echo(t_shell *data, char **command_args);
int			process_builtin(t_shell *data, t_cmd *last_node);
int			builtin_unset(t_shell *data, char **command_args);
int			builtin_export(t_shell *data, char **command_args);

#endif

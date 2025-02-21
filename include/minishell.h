/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/21 15:31:27 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include "../lib/library/inc/libft.h"
# include "definitions.h"
# include "error.h"
# include <dirent.h>
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

// ***************************************************************************
// **						Parsing Functions								**
// ***************************************************************************

int			parsing_syntax(t_shell *data);
int			validate_file_read_execution(t_file *rf);
int			check_access_fok(const char *path, int code);
int			check_access_xok(const char *path, int code);
void		identify_and_replace_sqpa_tokens(char *input);
int			check_is_directory(const char *path, int code);
int			validate_command_path_access(char *command_path);
void		strip_redirects(char *input, const char *redirects[]);

// ***************************************************************************
// **						Initialize Functions							**
// ***************************************************************************

size_t		hash(char *key);
t_shell		*get_shell(void);
t_hashmap	*create_map(void);
int			init_command(t_shell *data);
int			initialize_eof(t_shell *data);
int			main_shell_loop(t_shell *data);
bool		is_quotes_matching(char *input);
void		expand_wildcard(char **input_expanded);
void		update_envp_and_envpath(t_shell *data);
void		hashmap_delete(t_hashmap *map, char *key);
char		*hashmap_search(t_hashmap *map, char *key);
void		initialize_environment_paths(t_shell *data);
char		**process_command_input_expanded(t_cmd *command);
void		prepare_parameters(t_cmd *command, t_shell *data);
t_shell		*init_shell(int argc, char *argv[], char *envp[]);
char		*expand_command_input(char *input, bool *expanded);
void		hashmap_to_env_array(t_shell *data, t_hashmap *map);
void		import_env_to_hashmap(t_hashmap *map, char *envp[]);
int			hashmap_insert(t_hashmap *map, char *key, char *value);
char		*handle_command_elements(char **elements, bool *expanded);
int			match_wildcard(const char *pattern, const char *filename);
int			initialize_file_list(t_cmd *command, char *src,
				const char *redirects[]);
void		add_command(t_cmd **command, char *rl_splitted, t_shell *data,
				t_token id);

// ***************************************************************************
// **						Execution Functions								**
// ***************************************************************************

int			do_fork(pid_t *pid);
void		close_fd_safe(int fd);
void		run_commands(t_shell *data);
void		set_last_status(t_shell *data);
void		duplicate_fd(int fd1, int fd2);
int			run_eof(t_shell *data, t_cmd *command);
int			here_doc(int *pipe_id, t_file *current);
char		*get_path(char *input, char **env_paths);
void		open_folders_safety(int *io, t_file *rf);
void		do_dup2(int *io, int *pipe_id, int *prev_fd);
void		child_process(t_shell *data, t_cmd *command);
void		here_doc_fail(t_shell *data, t_file *current);
int			parent_process(t_shell *data, t_cmd **command_ref);

// ***************************************************************************
// **						Free Functions									**
// ***************************************************************************

void		cleanup_shell(t_shell *data);
void		hashmap_free(t_hashmap *map);
void		free_files(t_file *file_list);
void		hashnode_free(t_hashnode *head);
void		refresh_shell_data(t_shell *data);

// ***************************************************************************
// **						Utils Functions									**
// ***************************************************************************

void		skip_spaces(char **src);
void		debug_command_args(t_shell *data);
void		debug_command_path(t_shell *data);
void		insertion_sort(t_hashnode **head);
void		debug_command_input(t_shell *data);
void		debug_input_splitted(t_shell *data);
t_token		get_t_token(char *src, size_t size);
void		print_execve_parameters(char *input);
void		debug_command_file_list(t_shell *data);
void		restore_original_characters(char **src);
void		skip_character_by_idx(char *src, char c, int *i);
void		skip_character_diff_by_idx(char *src, char c, int *i);
void		replace_characters(char *src, char to_take, char to_put);
void		get_redir_segment(char *src, int *start, int *end,
				int redirect_size);

// ***************************************************************************
// **						BuiltIn											**
// ***************************************************************************

void		builtin_pwd(t_shell *data);
void		set_builtin_flag(t_cmd *last_node);
void		builtin_exit(t_shell *data, t_cmd *cmd);
int			builtin_cd(t_shell *data, char **command_args);
void		builtin_echo(t_shell *data, char **command_args);
int			builtin_unset(t_shell *data, char **command_args);
void		builtin_env(t_shell *data, t_cmd *command, int fd);
int			builtin_export(t_shell *data, t_cmd *command, int fd);
int			process_builtin(t_shell *data, t_cmd *command, int fd);

// ***************************************************************************
// **						Signal Functions								**
// ***************************************************************************

void		restore_signals(int code);
void		setup_parent_signals(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joralves <joralves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:50:06 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/31 16:02:13 by joralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
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
# include "definitions.h"


// ************************************************************************
// **						Parsing Functions							 **
// ************************************************************************

int			parsing_input(char *input);

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
int			init_command(char *input);

// ************************************************************************
// **						Proccess Functions						 	 **
// ************************************************************************

char		**get_command_args(char *argv);
void		execution(t_shell *data);
char 		*get_path(char *input, char **env_paths);
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

// void 		error_msg(void);

// ************************************************************************
// **						Error Functions							 	 **
// ************************************************************************

int 		handle_error(void);
void 		set_error(int code, const char *message, char *token, const char *function);

#endif

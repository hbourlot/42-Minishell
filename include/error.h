/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 16:35:41 by hbourlot          #+#    #+#             */
/*   Updated: 2025/02/10 17:51:54 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#ifndef ERROR_H
# define ERROR_H

# define E_SYNTAX_NEWLINE -1
# define E_SYNTAX_TOKEN -2
# define E_SHELL_SUPPORT -3
# define E_EOF -4
# define E_MALLOC -5
# define E_PF -6
# define E_VFRE -7
# define E_FILE_DIR -8
# define E_VCPA -9

# define SYNTAX_ERROR_MSG "bash: syntax error near unexpected token `"
# define NO_SUPPORT_MSG "bash: minishell doesn't support opened '"
# define NO_FILE_DIR_MSG "No such file or directory"

typedef struct s_execution
{
	bool				is_initialized;
	char				*msg;
	char				*folder;

}						t_execution;

typedef struct s_parsing
{
	bool				is_initialized;
	char				*syntax;
	char				*token;
}						t_parsing;

typedef struct s_initialize
{
	bool				is_initialized;
	char				*msg;
	char				*function;
}						t_initialize;

typedef struct s_error
{
	struct s_parsing	parsing;
	struct s_initialize	initialize;
	struct s_execution	execution;
	int					code;
	bool				exit;
}						t_error;

// ************************************************************************
// **						Error Functions								 **
// ************************************************************************

t_error					*get_error_context(void);
void					reset_error_context(t_error *error);
int						handle_error(int error, const char *token,
							const char *func);

int						handle_error_pa(void);
void					set_error_pa(int code, char *syntax, char *token);

int						handle_error_in(void);
void					set_error_in(int code, char *msg, const char *function,
							bool exit);

int						handle_error_ex(void);
void					set_error_ex(int code, char *msg, const char *folder,
							bool exit);

bool					is_tokens_invalid(char *rl);

#endif

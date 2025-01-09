#ifndef TESTS_H
#define TESTS_H

#include "library/inc/libft.h"
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

#define READ  	0
#define WRITE 	1
#define ERROR 	-1
#define OK		0

#ifndef CMP_OK
#define CMP_OK 0
#endif

#define SYNTAX_ERROR_MSG 	"bash: syntax error near unexpected token `"


typedef struct s_error
{
	int		code;
	char 	*message;
	char	*token;
	char	*function;
}	t_error;

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

typedef struct s_file
{
	char 			*read;
	char 			*write;
	t_delimiter 	delimiter;
	struct s_file 	*next;
}		t_file;

typedef struct s_cmd
{
	char	*input;
	t_file	*file;
	struct s_cmd *next;
}			t_cmd;



int		parsing_input(char *input);
void 	set_error(int code, const char *message, char *token, const char *function);
int 	handle_error(void);
void 	reset_error(t_error *error);


void debug_commands(t_cmd *cmd_list);
void debug_files(t_file *file_list);


#endif
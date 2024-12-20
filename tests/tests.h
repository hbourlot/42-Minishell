#ifndef TESTS_H
#define TESTS_H

#include "library/inc/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

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


int		parsing_input(char *input);
void 	set_error(int code, const char *message, char *token, const char *function);
int 	handle_error(void);
void 	reset_error(t_error *error);


#endif
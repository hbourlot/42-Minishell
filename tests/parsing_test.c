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



int main(int argc, char *argv[], char *envp[]) {
  
	// if (!*envp)
	// {
		char *env = getenv("ENV");
		if (env != NULL) {
			printf("PATH: %s\n", env);
		} else {
			printf("The ENV environment variable is not set.\n");
		}
		return 0;
	// }
    // char *path = getenv("PATH");
    
    // if (path != NULL) {
    //     printf("PATH: %s\n", path);
    // } else {
    //     printf("The PATH environment variable is not set.\n");
    // }

    return 0;
}

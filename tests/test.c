#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

static int	cleanup_and_exit(char *text, int error_code)
{
	if (text)
		free(text);
	write(1, "\n", 1);
	return (error_code);
}

static int	here_doc(char *limiter, int fd)
{
	int		i;
	char	*text;

	i = 0;
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		text = get_next_line(STDIN_FILENO);
		if (!text)
			return (-1);
		if (ft_strcmp(limiter, text) == CMP_OK)
			break ;
		if (ft_strlen(text) == 0) // TODO: CTRL + D: bash: warning: here-document at line 10 delimited by end-of-file (wanted `EOF')
			return (free(text), -1);
		if (!ft_strchr(text, '\n') && !ft_strncmp(text, limiter, ft_strlen(text)
				- 1))
			return (free(text), -1);
		ft_putstr_fd(text, fd);
		free(text);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[]) {
	
	int 	pipe_id[2];
	int		prev_fd;
	char 	*delimiter;
	pid_t	pid;

	char *path = "/bin/cat";
	char **args = ft_split("cat", ' ');

	prev_fd = -1;

	// ! FIRST PART
	if (pipe(pipe_id) < 0) {
		perror("Pipe process.\n");
		exit (EXIT_FAILURE);
	}

	pid = fork();
	if (pid < 0) {
		perror("Pid process.\n");
		exit (EXIT_FAILURE);
	}

	if (pid == 0) {
		close(pipe_id[0]);
		dup2(pipe_id[1], STDOUT_FILENO);
		delimiter = ft_strjoin("file", "\n");
		if (here_doc(delimiter, pipe_id[1]) < 0)
			perror("Here_doc");
		close(pipe_id[1]);
		free(delimiter);
		exit(EXIT_SUCCESS);
	}
	close(pipe_id[1]);
	waitpid(pid, NULL, 0);
	return (0);


}

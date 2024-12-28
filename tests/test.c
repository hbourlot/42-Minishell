#include "tests.h"

int	main(int argc, char *argv[], char *envp[]) {

	const char *env = "ls";
	char *r = getenv(env);
	printf("%s\n", r);
	return 0;
}

// int	main(int argc, char *argv[], char *envp[]) {
// 	(void)argc;
// 	(void)argv;

// 	int		pipe_id[2];
// 	pid_t	prev_fd;
// 	pid_t	pid;
// 	int		in_fd;
// 	int		out_fd;

// 	const char *path = "/bin/ls";
// 	const char *path1 = "/bin/cat";
// 	const char *path2 = "/usr/bin/grep";

// 	char **args = ft_split("ls", ' ');
// 	char **args1 = ft_split("cat", ' ');
// 	char **args2 = ft_split("grep p", ' ');

// 	if (pipe(pipe_id) < 0) {
// 		perror("Error creating first pipe");
// 		exit (EXIT_FAILURE);
// 	}

// 	pid = fork();
// 	if (pid < 0) {
// 		perror("Error on fork");
// 		exit (EXIT_FAILURE);
// 	}
// 	if (pid == 0) {
// 		in_fd = open("file", O_CREAT | O_RDWR, 0644);
// 		if (in_fd < 0) {
// 			perror("Opening file");
// 			exit (EXIT_FAILURE);
// 		}
// 		dup2(in_fd, STDIN_FILENO);
// 		dup2(pipe_id[1], STDOUT_FILENO);
// 		close(in_fd);
// 		close(pipe_id[0]);
// 		close(pipe_id[1]);

// 		execve(path1, args1, envp);
// 		perror("Execve path1");
// 		exit (EXIT_FAILURE);
// 	}

// 	prev_fd = pipe_id[0];
// 	close(pipe_id[1]);
	
// 	pid = fork();
// 	if (pid < 0) {
// 		perror("Error on fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid == 0) {
// 		dup2(prev_fd, STDIN_FILENO);
// 		close(prev_fd);
// 		execve(path, args, envp);
// 	}
// 	close(pipe_id[0]);
// 	return EXIT_SUCCESS;
// }

// int	main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;

// 	int		pipe_id[2];
// 	pid_t	prev_id;
// 	pid_t	pid;
// 	int		in_fd;
// 	int		out_fd;

// 	const char *path = "/bin/ls";
// 	const char *path1 = "/bin/cat";
// 	const char *path2 = "/usr/bin/grep";

// 	char **args = ft_split("ls", ' ');
// 	char **args1 = ft_split("cat", ' ');
// 	char **args2 = ft_split("grep p", ' ');

// 	if (pipe(pipe_id) < 0)
// 	{
// 		perror("Pipe1 creating failed");
// 		return (EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("Fork failed for first child");
// 		return (EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		in_fd = open("file", O_CREAT | O_RDWR, 0644);
// 		if (in_fd < 0) {
// 			perror("Failed to open file");
// 			return (EXIT_FAILURE);
// 		}
// 		dup2(in_fd, STDIN_FILENO);
// 		close(in_fd);

// 		dup2(pipe_id[1], STDOUT_FILENO);
// 		close(pipe_id[1]);
// 		close(pipe_id[0]);

// 		execve(path1, args1, envp);
// 		perror("Execve failed for 'cat'");
// 		exit (EXIT_FAILURE);
// 	}

// 	close(pipe_id[1]);
// 	prev_id = pipe_id[0];

// 	if (pipe(pipe_id) < 0) {
// 		perror("Pipe2 creation failed");
// 		return (EXIT_FAILURE);
// 	}

// 	pid = fork();
// 	if (pid < 0) {
// 		perror("Fork failed for second child");
// 		return (EXIT_FAILURE);
// 	}

// 	if (pid == 0) {
// 		dup2(prev_id, STDIN_FILENO);
// 		close(prev_id);
// 		close(pipe_id[0]);
// 		dup2(pipe_id[1], STDOUT_FILENO);
// 		close(pipe_id[1]);
// 		execve(path, args, envp);
// 		perror("ERROR LS\n");
// 	}

// 	pid = fork();
// 	if (pid < 0)
// 		return EXIT_FAILURE;
// 	if (pid == 0)
// 	{
// 		dup2(pipe_id[0], STDIN_FILENO);
// 		close(pipe_id[0]);
// 		close(pipe_id[1]);
// 		execve(path2, args2, envp);
// 		printf("ERROR\n");
// 		return (EXIT_FAILURE);
// 	}
// 	close(pipe_id[0]);
// 	close(pipe_id[1]);
// 	return (EXIT_SUCCESS);
// }

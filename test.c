#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char	**environ;

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_parent_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	main(void)
{
	char *input;
	pid_t pid;
	int status;

	setup_parent_signals();

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}

		signal(SIGINT, SIG_IGN);
			// Ignorar SIGINT en el padre durante la ejecución

		pid = fork();
		if (pid == 0)
		{ // Hijo
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			char *args[] = {"/bin/sh", "-c", input, NULL};
			execve(args[0], args, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{ // Padre
			do
			{
				if (waitpid(pid, &status, 0) == -1)
				{
					if (errno == EINTR)
						continue ;
					perror("waitpid");
					break ;
				}
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));

			if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGQUIT)
				{ // Manejar SIGQUIT específicamente
					write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
				}
				else
				{
					write(STDOUT_FILENO, "\n", 1);
				}
			}
		}
		else
		{
			perror("fork");
		}

		setup_parent_signals(); // Restaurar señales para el próximo input
		free(input);
	}

	return (0);
}
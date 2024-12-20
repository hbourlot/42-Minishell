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
# include "tests.h"

#ifndef CMP_OK
#define CMP_OK 0
#endif



int	count_redirects(char *input, const char *redirects[])
{
	int i;
	int	j;
	int	tot;
	int	idx_found;

	i = -1;
	tot = 0;
	sort_strings_by_length_desc((char **)redirects);
	while (input[++i])
	{
		j = -1;
		if (ft_strcmps(&input[i], redirects, &idx_found))
		{
			i += idx_found;
			tot++;
		}
	}
	return (tot);
}

char *get_first_word(char *src)
{
	int		i;
	int		start;
	char	*word;

	i = 0;
	while (src[i] && src[i] == ' ')
		i++;
	start = i;
	while (src[i] && src[i] != ' ')
		i++;
	return (ft_substr(&src[start], 0, i - start));
}

char	*next_word(char *src)
{
	int	i;

	while (src[i] && src[i] == ' ')
		i++;
	while (src[i] && src[i] != ' ')
		i++;
	return (src[i]);
}

char **get_files(char *input, const char *redirects[])
{
	int		i;
	int		j;
	int		nbr_of_files;
	char	**files[2];
	i = 0;
	sort_strings_by_length_desc((char **)redirects);
	nbr_of_files = count_redirects(input, redirects) + 1;

	
	// while (input[i])
	// {
	// 	while (j)
	// 	if (ft_strncmp(&input[i], redirects[j]))
	// }
	return (NULL);
}



int main(int argc, char *argv[], char *envp[]) {

	const char *delimiters[] = {"|", "||", "&&", NULL};
    const char *redirects[] = {">", ">>", "<", "<<", NULL};
    
    sort_strings_by_length_desc((char **)delimiters);
    sort_strings_by_length_desc((char **)redirects);
	if (parsing_input("echo  >echo oi > "))
		return (handle_error());
	// printf("NO error");

	// char	**files[2];
  	// char 	*args[] = {"cat", "oi", NULL};
	// get_files("test", redirects);
	// execve("/bin/cat", args, envp);

    return 0;
}

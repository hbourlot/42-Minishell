#include "libft.h"
#include <stdio.h>


static int	count_str(char *str, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != sep)
			count++;
		while (str[i] != sep)
			i++;
		if (str[i] == sep)
			count++;
		while (str[i] == sep)
			i++;
	}
	return (count);
}

char	**ft_split_keep_sep(char *str, char sep)
{
	char	**array;
	int		start;
	int		i;
	int		idx;

	idx = 0;
	start = 0;
	i = 0;
	array = malloc((count_str(str, sep) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (str && str[i])
	{
		while (str && str[i])
		{
			if (str[i] != sep)
				start = i;
			while (str[i] != sep)
			{
				i++;
				if (str[i] == '\0' || str[i] == sep)
					array[idx++] = ft_substr(str, start, i - start);
			}
			if (str[i] == sep)
				start = i;
			while (str[i] == sep)
			{
				i++;
				if (str[i] == '\0' || str[i] != sep)
					array[idx++] = ft_substr(str, start, i - start);
			}
		}
	}
	array[idx] = NULL;
	return (array);
}

/* int	main(void)
{
	int i = 0;

	char str[] = "'$USER' '$home'' '$path'";
	// printf("%d", count_str(str, '\''));
	char **array = ft_split_keep_sep(str, '\'');
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
} */
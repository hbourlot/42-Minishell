#include "tests.h"

int	count_redirects(char *input, const char *redirects[])
{
	int i;
	int	j;
	int	tot;
	int	idx;

	i = 0;
	tot = 0;
	sort_strings_by_length_desc((char **)redirects);
	while (input[i])
	{
		if (find_string_match(&input[i], redirects, &idx) == CMP_OK)
		{
			i += ft_strlen(redirects[idx]);
			tot++;
		}
		i++;
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

static char	*get_file_name(char *src, const char *redirects[])
{
	int	i;

	i = 0;
	while (src && *src)
	{
		while (*src && *src == ' ' || ft_strcmps(&src[i], redirects) == CMP_OK)
			src++;
		while (src[i] && src[i] != ' ' && ft_strcmps(&src[i], redirects) < 0)
			i++;
		return (ft_substr(src, 0, i));
	}
	return (NULL);
}

int	add_file(int mode, char *file_name, t_file **file_list, t_delimiter redirect)
{
	t_file	*current;
	t_file	*new_file;

	if (!file_list || !file_name || !*file_name)
		return (-1);
	new_file = ft_calloc(1, sizeof(t_file));
	if (!new_file)
		return (-1);
	if (mode == READ)
		new_file->read = file_name;
	else if (mode == WRITE)
		new_file->write = file_name;
	new_file->delimiter = redirect;
	if (!*file_list)
		*file_list = new_file;
	else
	{
		current = *file_list;
		// current = new_file;
		while (current->next)
			current = current->next;
		current->next = new_file;
	}
	return (0);
}

int	remove_file_and_redirect_from_input(char **input, const char *redirects[])
{
	int		start;
	int		end;
	int		idx;
	char	*to_remove;
	char	*new_input;

	start = 0;
	if (!input || !*input)
		return (-1);
	start = 0;
	while ((*input)[start])
	{
		if (find_string_match(&(*input)[start], redirects, &idx) == CMP_OK)
		{
			end = start + ft_strlen(redirects[idx]);
			while ((*input)[end] && (*input)[end] == ' ')
				end++;
			while ((*input)[end] && (*input)[end] != ' ' && ft_strcmps(&(*input)[end], redirects) < 0)
				end++;
			to_remove = ft_substr(*input, start, end - start);
			if (!to_remove)
				return (free(to_remove), -1);
			new_input = remove_substring(*(const char **)input, to_remove);
			if (!new_input)
				return (free(to_remove), -1);
			free(*input);
			free(to_remove);
			*input = new_input;
			continue;
		}
		start++;
	}
	return (0);
}

static int handle_file_redirection(t_cmd *command, char **input_tmp, const char *redirects[], int mode)
{
	t_delimiter redirect;
	char		*file_name;

	if (mode == READ)
		redirect = REDIRECT_LEFT_SINGLE;
	else
		redirect = REDIRECT_RIGHT_SINGLE;
	(*input_tmp)++;
	if (mode == READ && **input_tmp == '<')
		redirect = REDIRECT_LEFT_DOUBLE;
	else if (mode == WRITE && **input_tmp == '>')
		redirect = REDIRECT_RIGHT_DOUBLE;
	file_name = get_file_name(*input_tmp, redirects);
	if (!file_name || add_file(mode, file_name, &command->file, redirect))
	{
		if (file_name)
			free(file_name);
		return (-1);
	}
	return (0);
}

int parse_files(t_cmd *command, const char *redirects[])
{
	char 			*file_name;
	char			*input_tmp;
	int				idx_found;
	t_delimiter 	redirect;
	while (command)
	{
		input_tmp = command->input;
		while (input_tmp && *input_tmp)
		{
			if (*input_tmp == '>' && handle_file_redirection(command, &input_tmp, redirects, WRITE) < 0)
				return (-1);
			else if (*input_tmp == '<' && handle_file_redirection(command, &input_tmp, redirects, READ) < 0)
				return (-1);
			input_tmp++;
		}
		if (remove_file_and_redirect_from_input(&command->input, redirects) < 0)
			return (-1);
		command = command->next;
	}
	return (0);
}

void free_files(t_file *file_list)
{
	t_file *tmp;

	while (file_list)
	{
		tmp = file_list;
		if (tmp->read)
			free(tmp->read);
		if (tmp->write)
			free(tmp->write);
		file_list = file_list->next;
		free(tmp);
	}
}


void free_commands(t_cmd *cmd_list)
{
	t_cmd *tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		if (tmp->input)
			free(tmp->input);
		free_files(tmp->file);
		cmd_list = cmd_list->next;
		free(tmp);
	}
}


#include "tests.h"



int main(void)
{
	t_cmd *command_list = NULL; // Initialize your commands dynamically as needed
	const char *redirects[] = { ">", ">>", "<", "<<", NULL};

	char *input = "cat <input.txt>output.txt>>file2>file3";
	command_list = ft_calloc(1, sizeof(t_cmd));
	command_list->input = ft_strdup(input);
	sort_strings_by_length_desc((char **)redirects);
	// Example input parsing and processing
	if (parse_files(command_list, redirects) < 0)
	{
		fprintf(stderr, "Error parsing files.\n");
		free_commands(command_list);
		return EXIT_FAILURE;
	}
	debug_commands(command_list);
	free_commands(command_list);
	return EXIT_SUCCESS;
}


	// const char *delimiters[] = {"|", "||", "&&", NULL};
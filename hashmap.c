
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHMAP_SIZE 10

typedef struct s_hashnode
{
	char				*key;
	char				*value;
	struct s_hashnode	*next;
}						t_hashnode;

typedef struct s_hashmap
{
	t_hashnode			*slots[HASHMAP_SIZE];
}						t_hashmap;

size_t	hash(char *key)
{
	int		i;
	size_t	hash_value;

	hash_value = 0;
	i = 0;
	while (key[i])
	{
		hash_value += key[i] * (i + 1);
		i++;
	}
	return (hash_value % HASHMAP_SIZE);
}

t_hashnode	*find_node(t_hashmap *map, char *key)
{
	size_t		index;
	t_hashnode	*current;

	index = hash(key);
	current = map->slots[index];
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	insert(t_hashmap *map, char *key, char *value)
{
	size_t		index;
	t_hashnode	*current;
	t_hashnode	*new_node;

	current = find_node(map, key);
	if (current)
	{
		free(current->value);
		current->value = strdup(value);
		if (!current->value)
			return (-1);
		return (0);
	}
	index = hash(key);
		new_node = malloc(sizeof(t_hashnode));
	if (!new_node)
		return (-1);
	new_node->key = strdup(key);
	if (!new_node->key)
		return (free(new_node), -1);
	new_node->value = strdup(value);
	if (!new_node->value)
		return (free(new_node), free(new_node->key), -1);
	new_node->next = map->slots[index];
	map->slots[index] = new_node;
	return (0);
}

char	*search(t_hashmap *map, char *key)
{
	unsigned int	index;
	t_hashnode		*current;

	index = hash(key);
	current = map->slots[index];
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	display(t_hashmap *map)
{
	t_hashnode	*current;
	int			i;

	i = 0;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		while (current)
		{
			printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
		i++;
	}
}

void	free_map(t_hashmap *map)
{
	int			i;
	t_hashnode	*current;
	t_hashnode	*temp;

	i = 0;
	while (i < HASHMAP_SIZE)
	{
		current = map->slots[i];
		while (current)
		{
			temp = current;
			current = current->next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
		i++;
	}
}

t_hashmap	*create_map(void)
{
	static t_hashmap	map;

	bzero(&map, sizeof(t_hashmap)); // !!! ft_bzero or memset;
	return (&map);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hashmap	*map;

	map = create_map();
	insert(map, "HOME", "/user");
	insert(map, "PATH", "/bin/ls");
	display(map);
	free_map(map);
	return (0);
}

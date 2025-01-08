#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_lista
{
    void            *content;
    short           a;
    short           z;
    short           l;
    char            d;
    char            c;
    struct s_lista  *next;
}                   t_list2;

size_t get_offset(void *struct_ptr, void *member_ptr)
{
    printf("p: %p\n", (char *)member_ptr);  // Prints the address of member_ptr
    printf("p1: %p\n", (char *)struct_ptr); // Prints the address of struct_ptr
    return ((size_t)((char *)member_ptr - (char *)struct_ptr)); // Calculates and returns the offset
}

void *get_last_node(void *node, size_t next_offset)
{
    char *tmp;

    tmp = (char *)node;
    if (!tmp)
        return (NULL);
    while (*(void **)(tmp + next_offset))
        tmp = *(char **)(tmp + next_offset);
    return ((void *)tmp);
}

int main(int argc, char *argv[], char *envp[]) {
    
    t_list2 test;
    t_list2 test1;
	t_list2	test2;
	test.next = &test1;



    printf("Size of t_list2: %zu\n", sizeof(t_list2));
    size_t ptr_value = get_offset(&test, &(test.next));

	printf("Offset value: %zu\n", ptr_value);  // Expected: 16

	// t_list2 *tmp = get_last_node(&test, get_offset(&test, &(test.next))); 

	// printf("value: %d\n", tmp->a);
    
    return (0);
}
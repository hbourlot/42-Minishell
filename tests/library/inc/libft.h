/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourlot <hbourlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 20:49:30 by hbourlot          #+#    #+#             */
/*   Updated: 2024/12/19 19:19:52 by hbourlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// ! Functions in "./SRC/"

void				ft_bzero(void *s, size_t n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_itoa(int n);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *s, int c);
char				**ft_split(char const *s, char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

// ! Functions in "/BONUS/"
void				ft_lst_add_front(t_list **lst, t_list *new);
void				ft_lst_add_back(t_list **lst, t_list *new);
void				ft_lst_del_one(t_list *lst, void (*del)(void *));
void				ft_lst_clear(t_list **lst, void (*del)(void *));
void				ft_lst_iter(t_list *lst, void (*f)(void *));
int					ft_lst_size(t_list *lst);
t_list				*ft_lst_last(t_list *lst);
t_list				*ft_lst_new(void *content);
t_list				*ft_lst_map(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// * Added functions in "/UPD_SRC/"
int					ft_nbr_len(long nbr);
int					ft_line_len(char *src);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_itoa_iter(long nbr);
int					ft_check_duplicate(t_list **lst);
int					stack_value(t_list **node, int idx);
int					stack_idx(t_list **node, int value);
void				free_split(char **split);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
char				*ft_append_and_free(char *s1, char *s2);
long				ft_atol(const char *nptr);
char				*get_next_line(int fd);
int					ft_printf(const char *fmt, ...);
int					ft_putchar(char c);
int					ft_putstr(char *c);
int					array_length(char **src);
int					char_cmp(char a, char b);
int					is_str_longer(char *src1, char *src2);
int					is_greater(int a, int b);
char				*ft_strstr(const char *haystack, const char *needle);
char				**split_by_multiple_tokens(char *src, const char *tokens[]);
void				sort_strings_by_length_desc(char **arr);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*remove_substring(const char *source, char *to_remove);
int					ft_strcmps(const char *s1, const char *compers[], int *idx_found);
char				*ft_strstr_any(const char *haystack, const char **needles);


#endif

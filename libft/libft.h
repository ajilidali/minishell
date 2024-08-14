/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moajili <moajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:24:01 by hclaude           #+#    #+#             */
/*   Updated: 2024/08/14 18:14:22 by moajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2024
# endif

# define FREE_GB 1
# define FREE_PTR 2

// Garbage collector struct
typedef struct s_gc
{
	void			*str;
	struct s_gc		*next;
}					t_gc;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isprint(int c);
int					ft_isdigit(int a);
int					ft_strnum(char *str);
int					ft_isascii(int a);
int					ft_isalpha(int a);
int					ft_isalnum(int a);
const char			*ft_strstr(const char *str, const char *to_find);
int					ft_atoi(const char *nptr);
int					ft_lstsize(t_list *lst);
int					ft_strcmp(const char *s1, const char *s2);
long				ft_atol(const char *nptr);
char				*ft_strcat(char *s1, const char *s2);
char				*allocate_string(size_t length);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, unsigned int n);
char				*ft_itoa(int n);
char				*ft_replace(char *in, const char *replacee,
						const char *replaced);
char				*get_next_line(int fd);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strndup(const char *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				freetab(char **str);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_printf(const char *format,
						...) __attribute__((format(printf, 1, 2)));
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// garbage collector

int					ft_garbage(int flag, void *result);
void				*ft_malloc(size_t size);
void				ft_free(void *ptr);
void				ft_free_gb(void);
void				ft_exit(int status);

#endif

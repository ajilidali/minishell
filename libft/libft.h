/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakaido <sakaido@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:24:30 by moajili           #+#    #+#             */
/*   Updated: 2024/05/30 20:10:14 by sakaido          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char 				*ft_strcpy(char *dest, const char *src);
char				*ft_replace(char *in, const char *replacee, const char *replaced);
char				*ft_itoa(int n);
void				ft_freef(const char *format, ...);
void				*ft_memset(void *pointer, int value, size_t count);
void				*ft_memmove(void *dest, const void *source, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_memcmp(const void *pointer1, const void *pointer2,
						size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *memoryBlock, int searchedChar,
						size_t size);
char				*ft_ustrjoin(char *s1, char *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
int					ft_strlen(const char *c);
int					ft_isprint(int c);
int					ft_isdigit(int c);
char				*ft_strdup(const char *s1);
int					ft_strcmp(char *s1, char *s2);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
int					ft_isascii(int c);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalpha(int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char *s1, char *s2);
int					ft_isalnum(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *c);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strrchr(const char st[], int searchedChar);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *string, int searchedChar);
char				*ft_strnstr(const char *big, const char *lit, size_t len);
int					ft_strncmp(const char *s1, const char *s2, int n);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
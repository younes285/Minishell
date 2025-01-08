/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchreif <hchreif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:31:18 by hchreif           #+#    #+#             */
/*   Updated: 2024/08/27 14:02:09 by hchreif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);

int			ft_toupper(int a);
int			ft_tolower(int c);
int			ft_strncmp(char const *str1, char const *str2, size_t n);
int			ft_strcmp(char *s1, char *s2);

size_t		ft_strlen(const char *str);

void		*ft_memset(void *ptr, int v, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int ch, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
void		*ft_calloc(size_t num, size_t s);

size_t		ft_strlcat(char *dest, const char *s, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t n);
char		*ft_strdup(const char *str);
char		*ft_strnstr(const char *s, const char *f_s, size_t n);
char		*ft_strchr(const char *s, int ch);
char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const*s2);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strtrim(char const *s, char const *set);
char		**ft_split(char const *s, char c);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int nb, int fd);

int			ft_atoi(const char *num);
char		*ft_itoa(int n);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quelefev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:13:54 by quelefev          #+#    #+#             */
/*   Updated: 2025/01/21 15:14:09 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

/* get_next_line.c */
char	*get_next_line(int fd);
char	*get_line(char *mem_line);
void	get_rest(char *mem_line, char *buf);

/* get_next_line_utils.c */
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char *mem_line, char *buff);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *s);

#endif

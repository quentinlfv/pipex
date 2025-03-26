/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:34:44 by qlefevre          #+#    #+#             */
/*   Updated: 2025/03/25 18:09:36 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		infile;
	int		outfile;
	int		*pipefd;
	int		nbr_commands;
	int		index;
	char	*path;
	char	**all_path;
	char	*path_command;
	char	**arg_command;
}t_pipex;

/* main.c */
int			check(int argc, char **argv);
void		create_pipe(t_pipex *pipex);
void		close_pipe(t_pipex *pipex);
int			get_files(t_pipex *pipex, char *infile, char *outfile);

/* child.c */
char		*path(char **envp);
char		*find_path(char *cmd, char **all_path);
void		dup_dup2(int in_tube, int out_tube);
void		child(t_pipex pipex, char **argv, char **envp);

/* free.c */
void		free_pipefd(t_pipex pipex);
void		free_parent(t_pipex pipex);
void		free_child(t_pipex pipex);

/* utils.c */
int			close_doc(int fd);
int			strcmmp(const char *s1, const char *s2, int i);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);

/* functions.c */
char		**ft_split(char const *s, char c);
int			strnbr(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);

/* ft_printf */
void		ft_putnbr(int nbr, int *len);
void		ft_putchar(char c, int *len);
void		ft_putstr(char const *s, int *len);
void		ft_putnbr_u(unsigned int nbr, int *len);
void		ft_putnbr_p(va_list arg, int *len);
void		ft_putnbr_x(unsigned long nbr, int *len);
void		ft_putnbr_upx(unsigned long nbr, int *len);
void		ft_putnbr(int nbr, int *len);
int			ft_formats(char c, va_list args, int *len);
int			ft_printf(const char *s, ...);

#endif 

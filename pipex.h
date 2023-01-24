#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
    pid_t   pid[2];
    int     fd[2];
    int     pipefd[2];
    char    *path;
    char    **all_path;
    char    *path_cmd;
    char    **arg_command;

}t_pipex;

/* main.c */
int     check(int argc, char **argv);
void    free_all(t_pipex pipex);

/* child.c */
char    *path(char **envp);
char    *find_path(char *cmd, char **all_path);
void    child_one(t_pipex pipex, char **argv, char **envp);
void    child_two(t_pipex pipex, char **argv, char **envp);

/* utils.c */
int	    open_doc(char *doc);
int	    close_doc(int fd);
int	    strcmmp(const char *s1, const char *s2, int i);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int	    strnbr(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

#endif 
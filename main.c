#include "pipex.h"

void    free_all(t_pipex pipex)
{
    int i;

    i = 0;
    while (pipex.all_path[i])
    {
        free(pipex.all_path[i]);
        i++;
    }
    free(pipex.all_path);
}

int check(int argc, char **argv)
{
    *argv += 1;
    if (argc != 5)
        return (0);
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
    int     status;

    status = 0;
    if (!check(argc, argv))
        return (0);
    pipex.fd[0] = open(argv[1], O_RDONLY);
    if (pipex.fd[0] < 0)
        return (0);
    pipex.fd[1] = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    if (pipex.fd[1] < 0)
        return (close_doc(pipex.fd[0]), (0));
    pipex.path = path(envp);
    pipex.all_path = ft_split(pipex.path, ':');
    pipe(pipex.pipefd);
    pipex.pid[0] = fork();    
    if (pipex.pid[0] == 0)
    child_one(pipex, argv, envp);
    pipex.pid[1] = fork();
    if (pipex.pid[1] == 0)
    child_two(pipex, argv, envp);
    close_doc(pipex.pipefd[0]);
    close_doc(pipex.pipefd[1]);
    // close_doc(pipex.fd[0]);
    // close_doc(pipex.fd[1]);
    waitpid(pipex.pid[0], &status, 0);
    waitpid(pipex.pid[1], &status, 0);
    free_all(pipex);
    return (0);
}
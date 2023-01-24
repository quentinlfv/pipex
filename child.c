#include "pipex.h"

char    *path(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if(ft_strnstr(envp[i], "PATH", 4))
            return(envp[i] + 5);
        i++;
    }
    return (NULL);
}

char    *find_path(char *cmd, char **all_path)
{
    char    *tmp;
    char    *command;
    int     i;

    i = 0;  
    while (all_path[i])
    {
        tmp = ft_strjoin(all_path[i], "/");
        command = ft_strjoin(tmp, cmd);
        if (access(command, F_OK) == 0)
        {
            return (command);
        }
        i++;
    }
    return (NULL);
}

void    child_one(t_pipex pipex, char **argv, char **envp)
{
    //close_doc(pipex.pipefd[1]);
    dup2(pipex.pipefd[1], STDOUT_FILENO);
    close_doc(pipex.pipefd[0]);
    dup2(pipex.fd[0], STDIN_FILENO);
    pipex.arg_command = ft_split(argv[2], ' ');
    pipex.path_cmd = find_path(pipex.arg_command[0], pipex.all_path);
    // exit(execve(path_cmd, argv[2], envp));
    execve(pipex.path_cmd, pipex.arg_command, envp);
}

void    child_two(t_pipex pipex, char **argv, char **envp)
{
    //close_doc(pipex.pipefd[0]);
    dup2(pipex.pipefd[0], STDIN_FILENO);
    close_doc(pipex.pipefd[1]);
    dup2(pipex.fd[1], STDOUT_FILENO);
    pipex.arg_command = ft_split(argv[3], ' '); 
    pipex.path_cmd = find_path(pipex.arg_command[0], pipex.all_path);
    // exit(execve("PATH", argv[3], envp));
    execve(pipex.path_cmd, pipex.arg_command, envp);
}
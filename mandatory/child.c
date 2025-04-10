/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:12:10 by qlefevre          #+#    #+#             */
/*   Updated: 2025/04/10 11:24:47 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **all_path)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	if (all_path == NULL || !cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, F_OK) == 0)
		{
			return (command);
		}
		free(command);
		i++;
	}
	return (NULL);
}

void	child_one(t_pipex pipex, char **argv, char **envp)
{
	pipex.fd[0] = open(argv[1], O_RDONLY);
	if (pipex.fd[0] < 0)
	{
		perror(argv[1]);
		exit(1);
	}	
	close_doc(pipex.pipefd[0]);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	dup2(pipex.fd[0], STDIN_FILENO);
	close_doc(pipex.pipefd[1]);
	close_doc(pipex.fd[0]);
	pipex.arg_command = ft_split(argv[2], ' ');
	pipex.path_cmd = find_path(pipex.arg_command[0], pipex.all_path);
	if (!pipex.path_cmd)
	{
		ft_printf("command not found : %s\n", pipex.arg_command[0]);
		free_child(pipex);
		exit(127);
	}
	execve(pipex.path_cmd, pipex.arg_command, envp);
}

void	child_two(t_pipex pipex, char **argv, char **envp)
{
	pipex.fd[1] = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.fd[1] < 0)
	{
		perror(argv[4]);
		exit(1);
	}
	close_doc(pipex.pipefd[1]);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	dup2(pipex.fd[1], STDOUT_FILENO);
	close_doc(pipex.pipefd[0]);
	close_doc(pipex.fd[1]);
	pipex.arg_command = ft_split(argv[3], ' ');
	pipex.path_cmd = find_path(pipex.arg_command[0], pipex.all_path);
	if (!pipex.path_cmd)
	{
		ft_printf("command not found : %s\n", pipex.arg_command[0]);
		free_child(pipex);
		exit(127);
	}
	execve(pipex.path_cmd, pipex.arg_command, envp);
}

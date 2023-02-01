/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:12:10 by qlefevre          #+#    #+#             */
/*   Updated: 2023/01/26 15:15:41 by qlefevre         ###   ########.fr       */
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
	if (access(cmd, F_OK) == 0)
		return (cmd);
	if (all_path == NULL)
		return (NULL);
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
	close_doc(pipex.fd[1]);
	close_doc(pipex.pipefd[0]);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	dup2(pipex.fd[0], STDIN_FILENO);
	close_doc(pipex.pipefd[1]);
	close_doc(pipex.fd[0]);
	pipex.arg_command = ft_split(argv[2], ' ');
	pipex.path_cmd = find_path(pipex.arg_command[0], pipex.all_path);
	if (!pipex.path_cmd)
	{
		ft_printf("%s : command not found", pipex.arg_command[0]);
		free_child(pipex);
		exit(1);
	}
	execve(pipex.path_cmd, pipex.arg_command, envp);
}

void	child_two(t_pipex pipex, char **argv, char **envp)
{
	close_doc(pipex.fd[0]);
	close_doc(pipex.pipefd[1]);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	dup2(pipex.fd[1], STDOUT_FILENO);
	close_doc(pipex.pipefd[0]);
	close_doc(pipex.fd[1]);
	pipex.arg_command = ft_split(argv[3], ' ');
	pipex.path_cmd = find_path(pipex.arg_command[0], pipex.all_path);
	if (!pipex.path_cmd)
	{
		ft_printf("%s : command not found", pipex.arg_command[0]);
		free_child(pipex);
		exit(1);
	}
	execve(pipex.path_cmd, pipex.arg_command, envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:12:10 by qlefevre          #+#    #+#             */
/*   Updated: 2025/03/26 11:56:22 by quelefev         ###   ########.fr       */
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

void	dup_dup2(int in_tube, int out_tube)
{
	dup2(in_tube, STDIN_FILENO);
	dup2(out_tube, STDOUT_FILENO);
}

void	child(t_pipex pipex, char **argv, char **envp)
{
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		if (pipex.index == 0)
			dup_dup2(pipex.infile, pipex.pipefd[1]);
		else if (pipex.index == pipex.nbr_commands - 1)
			dup_dup2(pipex.pipefd[(pipex.index * 2) - 2], pipex.outfile);
		else
			dup_dup2(pipex.pipefd[(pipex.index * 2) - 2], pipex.pipefd[(pipex.index * 2) + 1]);
		close_pipe(&pipex);
		pipex.arg_command = ft_split(argv[2 + pipex.index], ' ');
		pipex.path_command = find_path(pipex.arg_command[0], pipex.all_path);
		if (!pipex.path_command)
		{
			ft_printf("Command not found : %s\n", pipex.arg_command[0]);
			free_child(pipex);
			exit(1);
		}
		execve(pipex.path_command, pipex.arg_command, envp);
	}
}

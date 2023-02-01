/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:52 by qlefevre          #+#    #+#             */
/*   Updated: 2023/01/26 15:08:57 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	check(int argc, char **argv)
{
	*argv += 1;
	if (argc != 5)
		return (0);
	return (1);
}

int	open_files(t_pipex *pipex, char **argv)
{
	pipex->fd[0] = open(argv[1], O_RDONLY);
	if (pipex->fd[0] < 0)
		return (perror(argv[1]), 0);
	pipex->fd[1] = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->fd[1] < 0)
		return (perror(argv[4]), close_doc(pipex->fd[0]), (0));
	return (1);
}

void	close_files(t_pipex *pipex)
{
	close_doc(pipex->pipefd[0]);
	close_doc(pipex->pipefd[1]);
	close_doc(pipex->fd[0]);
	close_doc(pipex->fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;
	int			status;

	status = 0;
	if (!check(argc, argv))
		return (0);
	if (!open_files(&pipex, argv))
		return (0);
	pipex.path = path(envp);
	if (pipex.path)
		pipex.all_path = ft_split(pipex.path, ':');
	else
		pipex.all_path = NULL;
	pipe(pipex.pipefd);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
		child_one(pipex, argv, envp);
	pipex.pid[1] = fork();
	if (pipex.pid[1] == 0)
		child_two(pipex, argv, envp);
	close_files(&pipex);
	waitpid(pipex.pid[0], &status, 0);
	waitpid(pipex.pid[1], &status, 0);
	free_parent(pipex);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:52 by qlefevre          #+#    #+#             */
/*   Updated: 2025/02/21 18:00:40 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	check(int argc, char **argv)
{
	*argv += 1;
	if (argc < 5)
	{
		ft_printf("Wrong numbers or arguments\n");
		return (0);
	}
	return (1);
}

void	close_files(t_pipex *pipex)
{
	close_doc(pipex->pipefd[0]);
	close_doc(pipex->pipefd[1]);
}

void	create_pipe(int **pipe_fd, int nbr_commands)
{
	int	i;

	i = 0;
	while (i < nbr_commands)
	{
		if (!pipe(pipefd + (2 * i)))
		{
			free_pipe(pipefd);
			return ;
		}
		i++;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;
	int			status;

	status = 0;
	if (!check(argc, argv))
		return (2);
	pipex.path = path(envp);
	if (pipex.path)
		pipex.all_path = ft_split(pipex.path, ':');
	else
		pipex.all_path = NULL;

	get_infile(pipex, argv[2]);
	get_outfile(pipex, argv[argc - 2]);
	pipex.nbr_commands = argc - 3;
	pipex.pipefd = malloc(sizeof(int) * (pipex.nbr_commands - 1) * 2);
	if (!pipex.pipefd)
	{
		free_path(pipex.all_path);
		free_pipefd(pipex.pipefd);
		return (0);
	}
	create_pipe(&pipex.pipefd, pipex.nbr_commands);
	/*
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
		child_one(pipex, argv, envp);
	pipex.pid[1] = fork();
	if (pipex.pid[1] == 0)
		child_two(pipex, argv, envp);
	*/
	pipex.index = 0; 
	while (pipex.index < pipex.nbr_commands)
	{
		child(pipex);
		pipex.index++;
	}
	close_files(&pipex);
	waitpid(pipex.pid[0], &status, 0);
	waitpid(pipex.pid[1], &status, 0);
	free_parent(pipex);
	return (status);
}

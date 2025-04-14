/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:52 by qlefevre          #+#    #+#             */
/*   Updated: 2025/04/14 13:47:20 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	check(int argc, char **argv)
{
	int	i;

	*argv += 1;
	if (argc != 5)
	{
		ft_printf("Wrong numbers or arguments\n");
		return (0);
	}
	i = 0;
	while (i < 5)
	{
		if (argv[i] == NULL || ft_strlen(argv[i]) == 0)
			return (ft_printf("Wrongs Args\n"), 0);
		i++;
	}
	return (1);
}

void	close_files(t_pipex *pipex)
{
	close_doc(pipex->pipefd[0]);
	close_doc(pipex->pipefd[1]);
}

int	exec(t_pipex pipex, char **argv, char **envp)
{
	int	exit_code;
	int	status;

	status = 0;
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
		child_one(pipex, argv, envp);
	pipex.pid[1] = fork();
	if (pipex.pid[1] == 0)
		child_two(pipex, argv, envp);
	close_files(&pipex);
	waitpid(pipex.pid[0], &status, 0);
	waitpid(pipex.pid[1], &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = 1;
	free_parent(pipex);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;
	int			exit_code;

	if (!check(argc, argv))
		return (2);
	pipex.path = path(envp);
	if (pipex.path)
		pipex.all_path = ft_split(pipex.path, ':');
	else
		pipex.all_path = NULL;
	pipe(pipex.pipefd);
	exit_code = exec(pipex, argv, envp);
	return (exit_code);
}

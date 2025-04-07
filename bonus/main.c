/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:52 by qlefevre          #+#    #+#             */
/*   Updated: 2025/04/07 16:56:07 by quelefev         ###   ########.fr       */
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

void	create_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_commands)
	{
		if (pipe(pipex->pipefd + 2 * i) == -1)
		{
			free_parent(*pipex);
			printf("exit\n");
			exit(0);
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_commands * 2)
	{
		close(pipex->pipefd[i]);
		i++;
	}
}

void	init_struct(t_pipex *pipex)
{
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->heredoc = 0;
	pipex->index = 0;
	pipex->nbr_commands = 0;
	pipex->pipefd = NULL;
	pipex->all_path = NULL;
	pipex->path_command = NULL;
	pipex->arg_command = NULL;
}

int	exec_pipex(int argc, char **argv, char **envp, t_pipex pipex)
{
	int status;

	status = 0;
	pipex.nbr_commands = argc - 3 - pipex.heredoc;
	pipex.pipefd = malloc(sizeof(int) * (pipex.nbr_commands) * 2);
	if (!pipex.pipefd)
	{
		free_parent(pipex);
		return (0);
	}
	create_pipe(&pipex);
	while (pipex.index < pipex.nbr_commands)
	{
		child(pipex, argv, envp);
		pipex.index++;
	}
	close_pipes(&pipex);

	waitpid(-1, &status, 0);
	close_files(&pipex);
	free_parent(pipex);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;

	if (!check(argc, argv))
		return (2);
	init_struct(&pipex);
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < 6)
			return (ft_printf("Wrong numbers of args!\n"), 2);
		else
			pipex.heredoc = 1;
	}
	if (!get_files(&pipex, argv, argv[1], argv[argc - 1]))
		return (0);
	pipex.path = get_path(envp);
	if (pipex.path)
		pipex.all_path = ft_split(pipex.path, ':');
	else
		pipex.all_path = NULL;
	return (exec_pipex(argc, argv, envp, pipex));
}

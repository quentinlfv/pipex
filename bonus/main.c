/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:52 by qlefevre          #+#    #+#             */
/*   Updated: 2025/03/26 15:40:57 by quelefev         ###   ########.fr       */
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
	close_doc(pipex->infile);
	close_doc(pipex->outfile);
}

int		get_files(t_pipex *pipex, char *infile_name, char *outfile_name)
{
	pipex->infile = open(infile_name, O_RDONLY);
	if (pipex->infile == -1)
	{
		ft_printf("Error\nfailed to open infile");
		return (0);
	}
	pipex->outfile = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if (pipex->outfile == -1)
	{
		ft_printf("Error\nfailed to open outfile");
		close(pipex->infile);
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

void	close_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_commands * 2)
	{
		close(pipex->pipefd[i]);
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
	
	if (!get_files(&pipex, argv[1], argv[argc - 1]))
	{
		free_parent(pipex);
		return (0);
	}
	
	pipex.nbr_commands = argc - 3;
	pipex.pipefd = malloc(sizeof(int) * (pipex.nbr_commands) * 2);
	if (!pipex.pipefd)
	{
		free_parent(pipex);
		return (0);
	}
	create_pipe(&pipex);
	pipex.index = 0; 
	while (pipex.index < pipex.nbr_commands)
	{
		child(pipex, argv, envp);
		pipex.index++;
	}
	close_pipe(&pipex);

	waitpid(-1, &status, 0);
	//waitpid(pipex.pid, &status, 0);
	close_files(&pipex);
	free_parent(pipex);
	return (status);
}

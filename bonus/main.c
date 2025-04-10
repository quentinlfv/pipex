/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:08:52 by qlefevre          #+#    #+#             */
/*   Updated: 2025/04/10 17:47:15 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

int	check(int argc, char **argv)
{
	int	i;

	*argv += 1;
	if (argc < 5)
	{
		ft_printf("Wrong numbers of arguments\n");
		return (0);
	}
	i = 0;
	while (i < argc)
	{
		if (argv[i] == NULL || ft_strlen(argv[i]) == 0)
			return (ft_printf("Wrongs args\n"), 0);
		i++;
	}
	return (1);
}

void	create_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmds)
	{
		if (pipe(pipex->pipefd + 2 * i) == -1)
		{
			free_parent(*pipex);
			ft_printf("Error while creating pipe\n");
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmds * 2)
	{
		close(pipex->pipefd[i]);
		i++;
	}
}

int	exec_pipex(int argc, char **argv, char **envp, t_pipex pipex)
{
	int	status;
	int	exit_code;

	status = 0;
	exit_code = 1;
	pipex.nbr_cmds = argc - 3 - pipex.heredoc;
	pipex.pipefd = malloc(sizeof(int) * (pipex.nbr_cmds) * 2);
	if (!pipex.pipefd)
		return (free_parent(pipex), 0);
	create_pipe(&pipex);
	while (pipex.index < pipex.nbr_cmds)
	{
		child(pipex, argv, envp);
		pipex.index++;
	}
	close_pipes(&pipex);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	close_files(&pipex);
	free_parent(pipex);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;

	if (!check(argc, argv))
		return (1);
	init_struct(&pipex);
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc < 6)
			return (ft_printf("Wrong numbers of args!\n"), 1);
		else
			pipex.heredoc = 1;
	}
	if (!get_files(&pipex, argv, argv[1], argv[argc - 1]))
		return (1);
	pipex.path = get_path(envp);
	if (pipex.path)
		pipex.all_path = ft_split(pipex.path, ':');
	else
		pipex.all_path = NULL;
	return (exec_pipex(argc, argv, envp, pipex));
}

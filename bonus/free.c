/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:24:28 by qlefevre          #+#    #+#             */
/*   Updated: 2025/04/10 15:30:38 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

void	free_parent(t_pipex pipex)
{
	int	i;

	i = 0;
	if (pipex.all_path)
	{
		while (pipex.all_path[i])
		{
			free(pipex.all_path[i]);
			i++;
		}
		free(pipex.all_path);
	}
	if (pipex.pipefd)
		free(pipex.pipefd);
}

void	free_child(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.arg_cmd[i])
	{
		free(pipex.arg_cmd[i]);
		i++;
	}
	free(pipex.arg_cmd);
	i = 0;
	if (pipex.all_path)
		free(pipex.all_path);
	if (pipex.pipefd)
		free(pipex.pipefd);
}

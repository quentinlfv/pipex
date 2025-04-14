/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:24:28 by qlefevre          #+#    #+#             */
/*   Updated: 2025/04/14 16:00:36 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

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
}

void	free_child(t_pipex pipex)
{
	int	i;

	i = 0;
	if (pipex.arg_command)
	{
		while (pipex.arg_command[i])
		{
			free(pipex.arg_command[i]);
			i++;
		}
		free(pipex.arg_command);
	}
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
}

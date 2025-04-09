/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quelefev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:44:51 by quelefev          #+#    #+#             */
/*   Updated: 2025/04/09 16:16:50 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"

void	init_struct(t_pipex *pipex)
{
	pipex->infile = 0;
	pipex->outfile = 0;
	pipex->heredoc = 0;
	pipex->index = 0;
	pipex->nbr_cmds = 0;
	pipex->pipefd = NULL;
	pipex->all_path = NULL;
	pipex->path_cmd = NULL;
	pipex->arg_cmd = NULL;
}

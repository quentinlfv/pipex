/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quelefev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:46:30 by quelefev          #+#    #+#             */
/*   Updated: 2025/04/09 16:23:18 by quelefev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"
#include "get_next_line.h"

void	close_files(t_pipex *pipex)
{
	close_doc(pipex->infile);
	close_doc(pipex->outfile);
	if (pipex->heredoc == 1)
		unlink(".heredoc.tmp");
}

void	get_heredoc(char *limiter)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open(".heredoc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0000644);
	printf("limiter : %s\n", limiter);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(line, heredoc_fd);
		free(line);
	}
	free(line);
	close(heredoc_fd);
}

int	get_files(t_pipex *pipex, char **argv, char *in_name, char *out_name)
{
	if (!get_infile(pipex, argv, in_name))
		return (0);
	if (!get_outfile(pipex, out_name))
		return (close(pipex->infile), 0);
	return (1);
}

int	get_infile(t_pipex *pipex, char **argv, char *infile_name)
{
	if (pipex->heredoc == 1)
	{
		get_heredoc(argv[2]);
		pipex->infile = open(".heredoc.tmp", O_RDONLY);
		if (pipex->infile == -1)
		{
			unlink(".heredoc.tmp");
			ft_printf("Error\nfailed to open infile\n");
			return (0);
		}
	}
	else
	{
		pipex->infile = open(infile_name, O_RDONLY);
		if (pipex->infile == -1)
		{
			ft_printf("Error\nfailed to open infile\n");
			return (0);
		}
	}
	return (1);
}

int	get_outfile(t_pipex *pipex, char *outfile_name)
{
	pipex->outfile = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if (pipex->outfile == -1)
	{
		ft_printf("Error\nfailed to open outfile\n");
		return (0);
	}
	return (1);
}

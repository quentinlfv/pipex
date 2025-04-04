#include "pipex.h"
#include "get_next_line.h"

void	close_files(t_pipex *pipex)
{
	close_doc(pipex->infile);
	close_doc(pipex->outfile);
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

int		get_files(t_pipex *pipex, char **argv, char *infile_name, char *outfile_name)
{
	if (pipex->heredoc == 1)
	{
		get_heredoc(argv[2]);
		pipex->infile = open(".heredoc.tmp", O_RDONLY);
	}
	else
	{
		pipex->infile = open(infile_name, O_RDONLY);
		if (pipex->infile == -1)
		{
			ft_printf("Error\nfailed to open infile");
			return (0);
		}
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

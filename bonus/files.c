#include "pipex.h"
#include "get_next_line.h"

void	close_files(t_pipex *pipex)
{
	close_doc(pipex->infile);
	close_doc(pipex->outfile);
}

int	get_heredoc(char *limiter)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDIN_FILENO);
		get_next_line(STDIN_FILENO);
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			break ;
		ft_putstr_fd(line, heredoc_fd);
		free(line);
	}
	free(line);
	return (heredoc_fd);
}

int		get_files(t_pipex *pipex, char **argv, char *infile_name, char *outfile_name)
{
	if (pipex->heredoc == 1)
		pipex->infile = get_heredoc(argv[2]);
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

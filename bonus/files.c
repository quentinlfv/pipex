#include "pipex.h"

void	get_infile(t_pipex *pipex, char *infile)
{
	pipex->fd[0] = open(infile, O_RDONLY);
	if (pipex->fd[0] < 0)
	{
		ft_printf("Error\nFile cant be open\n");
	}
}

void	get_outfile(t_pipex *pipex, char *outfile)
{
	pipex->fd[1] = open(outfile, O_CREAT | O_WRONLY | O_TRUNC);
	if (pipex->fd[1] < 0)
	{
		ft_printf("Error\nFile cant be open\n");
	}
}

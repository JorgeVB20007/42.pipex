#include "pipex.h"

void	infile_nf(char *file)
{
	int	a;

	a = 0;
	write(1, ".zsh: no such file or directory: ", 32);
	while (file[a])
	{
		write(1, &file[a], 1);
		a++;
	}
	write(1, "\n", 1);
	exit (0);
}

void	infile_pd(char *file)
{
	int	a;

	a = 0;
	write(1, ".zsh: permission denied: ", 24);
	while (file[a])
	{
		write(1, &file[a], 1);
		a++;
	}
	write(1, "\n", 1);
	exit (0);
}
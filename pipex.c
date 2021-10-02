#include "pipex.h"

void	child_one(char *argv, char **envp, int fdin, int fd[2])
{
	close(fd[0]);
	dup2(fdin, STDIN_FILENO); 
	close(fd[1]);
	execve("/bin/cat", ft_split(argv, ' '), envp);
}

void	child_two(char *argv, char **envp, int fdout, int fd[2])
{
	close(fd[1]);
	dup2(fdout, STDOUT_FILENO); 
	close(fd[0]);
	execve("/bin/cat", ft_split(argv, ' '), envp);
}

void	pipex(char **argv, char **envp, int fdin, int fdout)
{
	int	relative;
	int	fd[2];

	pipe(fd);
	relative = fork();
	if (!relative)
		child_one(argv[2], envp, fdin, fd);
		else
		{
			relative = fork();
			if (!relative)
				child_two(argv[3], envp, fdin, fd);
		}

}

int main(int argc, char **argv, char **envp)
{
	int	fdin;
	int	fdout;

	fdin = open(argv[1], 0);
	fdout = open(argv[4], 0);
	pipex(argv, envp, fdin, fdout);

	return (0);
}
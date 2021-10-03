#include "pipex.h"

void	child_one(char *argv, char **envp, int fdin, int fd[2])
{
	close(fd[0]);
	dup2(fdin, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
//	close(fd[1]);
	close(fdin);
	execve("/bin/cat", ft_split(argv, ' '), envp);
}

void	child_two(char *argv, char **envp, int fdout, int fd[2])
{
//	close(fd[1]);
	char *test = malloc(25);
	test[9] = 24;
	read(fd[0], test, 24);
	printf("\n\n>%s<\n\n", test);
	dup2(fd[0], STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	close(fd[0]);
	execve("/bin/wc", ft_split(argv, ' '), envp);
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
			child_two(argv[3], envp, fdout, fd);
	}
	wait(&relative);
}

int main(int argc, char **argv, char **envp)
{
	int	fdin;
	int	fdout;

	if (argc != 5)
		return (0);
	fdin = open(argv[1], 0);
	fdout = open(argv[4], 1);
	pipex(argv, envp, fdin, fdout);

	return (0);
}
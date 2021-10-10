#include "pipex.h"

char	*getgoodpath(char **envp, char *command)
{
	char	**result;
	int		a;
	char	*attempt;

	a = 0;
	command = ft_strjoin("/", command);
	while (envp[a] != NULL)
	{
		if (envp[a][0] == 'P' && envp[a][1] == 'A' && envp[a][2] == 'T' \
		&& envp[a][3] == 'H' && envp[a][4] == '=')
		{
			result = ft_split(&envp[a][5], ':');
			break;
		}
		a++;
	}
	a = 0;
	while (result[a] != NULL)
	{
		attempt = ft_strjoin(result[a], command);
		if (!access(attempt, X_OK))
			return (attempt);
		free (attempt);
		a++;
	}
	infile_nf(command);
	return (NULL);
}

void	just_do_it(char *command, char **envp)
{
	char	**splittedcommand;
	char	**splittedtwo;
	char	**splittedthree;
	int		a;

	splittedcommand = ft_split(command, ' ');
	splittedthree = ft_split(command, ' ');
	a = 0;
	if (!access(splittedcommand[0], X_OK))
	{
		splittedtwo = ft_split(splittedcommand[0], '/');
		while (splittedtwo[a])
			a++;
		free(splittedthree[0]);
		splittedthree[0] = splittedtwo[a - 1];
		execve(splittedcommand[0], splittedthree, envp);
	}
	else
	{
		execve(getgoodpath(envp, splittedcommand[0]), splittedcommand, envp);
	}
}

void child_one(int pip[2], char *in_file, char *command, char **envp)
{
	int		fd;
	char	**splittedcommand;
	char	**splittedtwo;

	close(pip[0]);
	fd = open(in_file, 0);
	dup2(pip[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pip[1]);
	close(fd);
	just_do_it(command, envp);
}

void child_two(int pip[2], char *out_file, char *command, char **envp)
{
	int		fd;
	char	**splittedcommand;

	close(pip[1]);
	splittedcommand = ft_split(command, ' ');
	fd = open(out_file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(pip[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(pip[0]);
	just_do_it(command, envp);
//	execve(getgoodpath(envp, splittedcommand[0]), splittedcommand, envp);
}

int main(int argc, char **argv, char **envp)
{
	int		pip[2];
	pid_t	ischildone;
	pid_t	ischildtwo;

	if (access(argv[1], 0))
		infile_nf(argv[1]);
	else if (access(argv[1], R_OK))
		infile_pd(argv[1]);
	else if (!access(argv[4], 0) && access(argv[4], W_OK))
		infile_pd(argv[4]);
	pipe(pip);
	if (argc != 5)
	{
		write(1, "Error: must include 4 arguments.\n", 33);
		return (0);
	}
	ischildone = fork();
	if (ischildone == -1)
		return (0);
	else if (!ischildone)
		child_one(pip, argv[1], argv[2], envp);
	else
	{
		ischildtwo = fork();
		if (ischildtwo == -1)
			return (0);
		else if (!ischildtwo)
			child_two(pip, argv[4], argv[3], envp);
		close(pip[0]);
		close(pip[1]);
	}
	waitpid(ischildone, 0, 0);
	waitpid(ischildtwo, 0, 0);
}

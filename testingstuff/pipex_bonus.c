/*#include "pipex.h"

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
	while (result != NULL)
	{
		attempt = ft_strjoin(result[a], command);
		if (!access(attempt, X_OK))
			return (attempt);
		free (attempt);
		a++;
	}
	return (NULL);
}

void child_one(int pip[2], char *in_file, char *command, char **envp)
{
	int		fd;
	char	**splittedcommand;

	close(pip[0]);
	fd = open(in_file, 0);
	dup2(pip[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pip[1]);
	close(fd);
	if (!access(command, X_OK))
	{
		write(1, "Access granted!\n\n", 17);
		splittedcommand = ft_split(command, '/');
		fd = 0;
		while (splittedcommand[fd])
			fd++;
		execve(command, &splittedcommand[fd - 1], envp);
	}
	else
	{
		write(1, "Path found!\n\n", 13);
		splittedcommand = ft_split(command, ' ');
		execve(getgoodpath(envp, splittedcommand[0]), splittedcommand, envp);
	}

}

void child_half(int oldpip[2], int newpip[2], char *command, char **envp)
{
	int		fd;
	char	**splittedcommand;

	splittedcommand = ft_split(command, ' ');
	close(newpip[0]);
	close(oldpip[1]);
	dup2(oldpip[0], STDIN_FILENO);
	dup2(newpip[1], STDOUT_FILENO);
	close(fd);
	close(oldpip[0]);
	close(newpip[1]);
	execve(getgoodpath(envp, splittedcommand[0]), splittedcommand, envp);
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
	execve(getgoodpath(envp, splittedcommand[0]), splittedcommand, envp);
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
	else if (access(argv[4], W_OK) && !access(argv[4], 0))
		infile_pd(argv[4]);
	pipe(pip);
	if (argc != 5)
		return (0);
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
*/
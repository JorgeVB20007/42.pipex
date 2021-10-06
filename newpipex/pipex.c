#include "pipex.h"

char	*getgoodpath(char **envp, char *command)
{
	char	**result;
	int		a;

	a = 0;
	while (envp[a] != NULL)
	{
		if (envp[a][0] == 'P' && envp[a][1] == 'A' && envp[a][2] == 'T' \
		&& envp[a][3] == 'H' && envp[a][4] == '=')
			result = ft_split(&envp[a][5], ':');
		a++;
	}
	a = 0;
	return (NULL);
}

void child_one(int pip[2], char *in_file, char *command, char **envp)
{
	int	fd;

	fd = open(in_file, 0);
	close(pip[0]);
	dup2(pip[1], STDOUT_FILENO);
	dup2(in_file, STDIN_FILENO);
	execve()
}

void child_two(int pip[2], char *out_file, char *command, char **envp)
{

}

int main(int argc, char **argv, char **envp)
{
	int		pip[2];
	pid_t	ischildone;
	pid_t	ischildtwo;

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
	}
	waitpid(ischildone, 0, 0);
	waitpid(ischildtwo, 0, 0);
}

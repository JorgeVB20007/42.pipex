#include "pipex.h"

char	*find_good_path(char **pathlist, char *suffix)
{
	int		a;
	int		acs;
	char	*command_path;

	a = 0;
	acs = -1;
	pathlist[0] = &pathlist[0][5];
	suffix = ft_strjoin("/", suffix);
	while (pathlist[0] != NULL)
	{
		command_path = ft_strjoin(pathlist[a], suffix);
		printf("%s\n", command_path);
		acs = access(command_path, X_OK);
		if (acs > -1)
		{
//			printf("\n     >> %s <<\n", command_path);
			return (command_path);
		}
		free(command_path);
		a++;
	}
	return (NULL);
}

char	*get_path_list(char **envp)
{
	int	a;

	a = 0;
	while (envp[a] != NULL)
	{
		if (envp[a][0] == 'P' && envp[a][1] == 'A' && envp[a][2] == 'T' \
		&& envp[a][3] == 'H' && envp[a][4] == '=')
			return (&envp[a][5]);
		a++;
	}
	return (NULL);
}

void	child_one(char *argv, char **envp, int fdin, int fd[2])
{
	char	**command;
	char	*gdenvp;

	gdenvp = get_path_list(envp);
	command = ft_split(argv, ' ');
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fdin, STDIN_FILENO);
	close(fd[1]);
	close(fdin);
	execve(find_good_path(ft_split(gdenvp, ':'), command[0]), command, envp);
}

void	child_two(char *argv, char **envp, int fdout, int fd[2])
{
	char	**command;
	char	*gdenvp;

	gdenvp = get_path_list(envp);
	command = ft_split(argv, ' ');
	dup2(fd[0], STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	close(fd[0]);
	close(fdout);
	execve(find_good_path(ft_split(gdenvp, ':'), command[0]), command, envp);
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
		else
		{
			waitpid(relative, 0, 0);
			exit (0);
		}
	}
}

int	checkaccess(char *path)
{
	return (access(path, X_OK));
}


int main(int argc, char **argv, char **envp)
{
	int		fdin;
	int		fdout;
//	char	shortenvp;

	if (argc != 5)
		return (0);
	if (access(argv[1], R_OK) != 0)
		return (0);
//	shortenvp = get_path_list(envp);
//	printf("\n\nAccess: %d\n\n", checkaccess("/bin/cat"));
//	printf("\n\nAccess: %d\n\n", checkaccess(argv[4]));
//	find_good_path(ft_split(envp[6], ':'), "/norminette");
//	find_good_path(ft_split(envp[6], ':'), "/git");
//	find_good_path(ft_split(envp[6], ':'), "/ssh");
	fdin = open(argv[1], 0);
	fdout = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0666);
	pipex(argv, envp, fdin, fdout);
	close (fdin);
	close (fdout);
	return (0);
}

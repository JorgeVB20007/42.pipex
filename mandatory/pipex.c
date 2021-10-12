/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:41:04 by jvacaris          #+#    #+#             */
/*   Updated: 2021/10/12 21:41:05 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child_one(int pip[2], char *in_file, char *command, char **envp)
{
	int		fd;
	int		a;

	a = 0;
	if (access(in_file, 0))
		problem("pipex: no such file or directory: ", in_file, 1);
	else if (access(in_file, R_OK))
		problem("pipex: permission denied: ", in_file, 1);
	close(pip[0]);
	fd = open(in_file, 0);
	dup2(pip[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	a = just_do_it(command, envp);
	close(pip[1]);
	exit (a);
}

int	child_two(int pip[2], char *out_file, char *command, char **envp)
{
	int	fd;
	int	a;

	close(pip[1]);
	fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		problem("pipex: open failed", "", 1);
		exit (-1);
	}
	dup2(pip[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	a = just_do_it(command, envp);
	close(pip[0]);
	exit (a);
}

int	parent(pid_t ischildtwo, int pip[2], char **argv, char **envp)
{
	int	ret;

	ret = 0;
	ischildtwo = fork();
	if (ischildtwo == -1)
		problem("pipex: fork failed", "", 1);
	else if (!ischildtwo)
		ret = child_two(pip, argv[4], argv[3], envp);
	close(pip[0]);
	close(pip[1]);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	int		pip[2];
	pid_t	ischildone;
	pid_t	ischildtwo;
	int		ret;

	ret = 0;
	if (argc != 5)
		problem("pipex: 4 arguments required ", "", 1);
	if (!access(argv[4], 0) && access(argv[4], W_OK))
		problem("pipex: permission denied: ", argv[4], 1);
	pipe(pip);
	ischildtwo = 0;
	ischildone = fork();
	if (ischildone == -1)
		problem("pipex: fork failed", "", 1);
	else if (!ischildone)
		child_one(pip, argv[1], argv[2], envp);
	else
		parent(ischildtwo, pip, argv, envp);
	waitpid(ischildone, 0, 0);
	waitpid(ischildtwo, 0, 0);
	return (ret);
}

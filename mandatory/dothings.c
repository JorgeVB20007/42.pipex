/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dothings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:55:49 by jvacaris          #+#    #+#             */
/*   Updated: 2021/10/12 21:55:50 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*getgoodpath_two(char *command, char **commandtwo, char ***result)
{
	int		a;
	char	*attempt;

	a = 0;
	while ((*result)[a] != NULL)
	{
		attempt = ft_strjoin((*result)[a], *commandtwo);
		if (!access(attempt, X_OK))
			return (attempt);
		free (attempt);
		a++;
	}
	doublefree(result);
	free (*commandtwo);
	if (command[0] == '/')
		problem("pipex: no such file or directory: ", command, 1);
	else
		problem("pipex: command not found: ", command, 1);
	return (NULL);
}

char	*getgoodpath(char **envp, char *command)
{
	char	**result;
	int		a;
	char	*commandtwo;

	a = 0;
	if (!envp)
		exit (0);
	commandtwo = ft_strjoin("/", command);
	result = NULL;
	while (envp[a] != NULL)
	{
		if (envp[a][0] == 'P' && envp[a][1] == 'A' && envp[a][2] == 'T' \
		&& envp[a][3] == 'H' && envp[a][4] == '=')
		{
			result = ft_split(&envp[a][5], ':');
			break ;
		}
		a++;
	}
	if (!result)
		exit (0);
	return (getgoodpath_two(command, &commandtwo, &result));
}

static int	just_do_it_two(char ***sthree, char **splittedcomm, char **envp)
{
	int		a;
	char	**splittedtwo;

	a = 0;
	splittedtwo = ft_split(splittedcomm[0], '/');
	while (splittedtwo[a])
		a++;
	free((*sthree)[0]);
	(*sthree)[0] = splittedtwo[a - 1];
	a = execve(splittedcomm[0], (*sthree), envp);
	doublefree(&splittedtwo);
	return (a);
}

int	just_do_it(char *command, char **envp)
{
	char	**splittedcomm;
	char	**splittedthree;
	int		a;
	char	*ggp;

	ggp = NULL;
	splittedcomm = ft_split(command, ' ');
	splittedthree = ft_split(command, ' ');
	a = 0;
	if (!access(splittedcomm[0], X_OK))
	{
		just_do_it_two(&splittedthree, splittedcomm, envp);
	}
	else
	{
		ggp = getgoodpath(envp, splittedcomm[0]);
		a = execve(ggp, splittedcomm, envp);
		free (ggp);
	}
	doublefree(&splittedcomm);
	doublefree(&splittedthree);
	return (a);
}

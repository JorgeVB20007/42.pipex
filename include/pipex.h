/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 22:27:38 by jvacaris          #+#    #+#             */
/*   Updated: 2021/10/12 22:27:42 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_input
{
	char	*comm1;
	char	*comm2;
}					t_input;

int		main(int argc, char **argv, char **envp);
void	problem(char *prefix, char *file, int exitcode);
void	doublefree(char ***ptp);
char	*getgoodpath(char **envp, char *command);
int		just_do_it(char *command, char **envp);

#endif

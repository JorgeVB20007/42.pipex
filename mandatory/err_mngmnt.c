/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mngmnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvacaris <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:40:52 by jvacaris          #+#    #+#             */
/*   Updated: 2021/10/12 21:40:53 by jvacaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	problem(char *prefix, char *file, int exitcode)
{
	int	a;

	a = 0;
	while (prefix[a])
		write(2, &prefix[a++], 1);
	a = 0;
	while (file[a])
		write(2, &file[a++], 1);
	write(2, "\n", 1);
	exit (exitcode);
}

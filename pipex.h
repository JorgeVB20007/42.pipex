#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <unistd.h>
# include <stdio.h

typedef struct s_input
{
	char	*comm1;
	char	*comm2;
}					t_input;

int		main(int argc, char **argv);

#endif
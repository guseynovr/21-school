#ifndef PIPEX_H
# define PIPEX_H

# define PATH "PATH="
# define EINVARG "usage: pipex file1 cmd1 cmd2 file2\n"
# define EINVARG_B "usage: pipex (\"<<\" delimiter | file1)\
 [cmd1 cmd2 ...] [\">>\"] file2\n"
# define PIPEX "pipex"
# define ENOTFOUND ": command not found\n"
# define PHEREDOC "pipex heredoc>"

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"

void	error(char *msg);
char	*join_three(char *s1, char *s2, char *s3);
void	free_nta(char **tab);
void	no_cmd(char **args);
int		open_file(char *filename, int flags);
void	try_exec(char *arg);
char	**get_paths(void);

#endif

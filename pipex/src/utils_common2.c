#include "pipex.h"

void	try_exec(char *arg)
{
	extern char	**environ;
	char		**paths;
	char		**args;
	char		*fn;
	int			i;

	paths = get_paths();
	if (!paths)
		exit(1);
	args = ft_split(arg, ' ');
	if (!args)
		exit(1);
	if (ft_strcmp(">>", *args) && ft_strcmp("<<", *args))
	{
		execve(*args, args, environ);
		i = 0;
		while (paths[i])
		{
			fn = join_three(paths[i++], "/", args[0]);
			execve(fn, args, environ);
		}
	}
	free_nta(paths);
	no_cmd(args);
}

int	open_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
		error(filename);
	return (fd);
}

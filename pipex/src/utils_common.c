#include "pipex.h"

void	error(char *msg)
{
	if (!ft_strcmp(EINVARG, msg) || !ft_strcmp(EINVARG_B, msg))
		ft_putstr_fd(msg, 2);
	else
	{
		msg = ft_strjoin("pipex: ", msg);
		if (!msg)
			exit(ENOMEM);
		perror(msg);
		free(msg);
	}
	exit(1);
}

char	*join_three(char *s1, char *s2, char *s3)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

void	free_nta(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	no_cmd(char **args)
{
	char	*err_msg;
	char	*tmp;

	if (args)
		tmp = join_three(PIPEX, ": ", args[0]);
	else
		tmp = join_three(PIPEX, ": ", "");
	err_msg = ft_strjoin(tmp, ENOTFOUND);
	free(tmp);
	ft_putstr_fd(err_msg, 2);
	free(err_msg);
	free_nta(args);
	exit(1);
}

char	**get_paths(void)
{
	char		**paths;
	char		*index;
	extern char	**environ;

	while (*environ)
	{
		index = ft_strnstr(*environ, PATH, ft_strlen(*environ));
		if (index && *environ == index)
		{
			paths = ft_split(*environ + ft_strlen(PATH), ':');
			if (!paths)
				return (0);
			return (paths);
		}
		environ++;
	}
	return (0);
}

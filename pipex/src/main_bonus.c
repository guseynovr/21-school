#include "pipex.h"

void	prep_pps(int *pipefd, int *hpipe, int pipe_in, int outfd)
{
	close(pipefd[0]);
	if (hpipe)
	{
		close(hpipe[1]);
		dup2(hpipe[0], 0);
	}
	else
		dup2(pipe_in, 0);
	if (outfd >= 0)
		dup2(outfd, 1);
	else
		dup2(pipefd[1], 1);
}

int	new_fork(char *arg, int pipe_in, int outfd, int *hpipe)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (!*arg)
		no_cmd(0);
	if (pipe(pipefd) < 0)
		error("pipe");
	pid = fork();
	if (!pid)
	{
		prep_pps(pipefd, hpipe, pipe_in, outfd);
		try_exec(arg);
	}
	else
	{
		close(pipefd[1]);
		if (hpipe)
		{
			close(hpipe[0]);
			close(hpipe[1]);
		}
		waitpid(pid, &status, 0);
	}
	return (pipefd[0]);
}

void	last_fork(char **argv, int input_fd)
{
	int	flags;

	if (!ft_strcmp(argv[1], ">>"))
	{
		if (!argv[2])
			error(EINVARG_B);
		flags = O_CREAT | O_WRONLY | O_APPEND;
		new_fork(argv[0], input_fd, open_file(argv[2], flags), 0);
	}
	else
	{
		flags = O_CREAT | O_WRONLY | O_TRUNC;
		new_fork(argv[0], input_fd, open_file(argv[1], flags), 0);
	}
}

void	heredoc(char *delimiter, int *hdpipe)
{
	char	*line;
	int		ret;

	ft_putstr_fd(PHEREDOC, 1);
	ret = get_next_line(0, &line);
	while (ft_strcmp(delimiter, line))
	{
		ft_putstr_fd(line, hdpipe[1]);
		ft_putchar_fd('\n', hdpipe[1]);
		if (ret > 0)
			ft_putstr_fd(PHEREDOC, 1);
		free(line);
		ret = get_next_line(0, &line);
	}
}

int	main(int argc, char **argv)
{
	int		input_fd;
	int		hpipe[2];
	int		*hp;

	if (argc < 5)
		error(EINVARG);
	hp = 0;
	if (!ft_strcmp("<<", *++argv))
	{
		pipe(hpipe);
		heredoc(*++argv, hpipe);
		argc--;
		hp = hpipe;
	}
	else
		input_fd = open_file(*argv, O_RDONLY);
	while (--argc > 3)
	{
		if (argc == 4 && !ft_strcmp(argv[2], ">>"))
			break ;
		input_fd = new_fork(*++argv, input_fd, -1, hp);
		hp = 0;
	}
	last_fork(++argv, input_fd);
	close(input_fd);
}

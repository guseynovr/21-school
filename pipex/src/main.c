#include "pipex.h"

int	new_fork(char *arg, int pipe_in, int outfd)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (*arg == 0)
		no_cmd(0);
	if (pipe(pipefd) < 0)
		error("pipe");
	pid = fork();
	if (!pid)
	{
		close(pipefd[0]);
		dup2(pipe_in, 0);
		if (outfd >= 0)
			dup2(outfd, 1);
		else
			dup2(pipefd[1], 1);
		try_exec(arg);
	}
	else
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
	}
	return (pipefd[0]);
}

int	main(int argc, char **argv)
{
	int		input_fd;

	if (argc != 5)
		error(EINVARG);
	input_fd = open_file(*++argv, O_RDONLY);
	while (--argc > 3)
		input_fd = new_fork(*++argv, input_fd, -1);
	new_fork(argv[1], input_fd,
		open_file(argv[2], O_CREAT | O_WRONLY | O_TRUNC));
	close(input_fd);
}

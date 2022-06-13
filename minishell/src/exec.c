/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:33:03 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 20:38:35 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_child_routine(t_command *cmd, char **env)
{
	char		**args;
	struct stat	statbuf;

	if (redirect(cmd->redirects) == ERR)
		exit(g_sh.last_return);
	if (!cmd->words)
		exit(OK);
	if (init_arrlst(cmd->words, &args, FALSE) == ERR)
		exit(g_sh.last_return);
	if (cmd->fullpath == cmd->words->content
		&& !is_path_specified(cmd->fullpath))
		exit(error_exec(args[0], ENOENT) + 1 + g_sh.last_return);
	else if (cmd->fullpath == cmd->words->content
		&& is_path_specified(cmd->fullpath))
	{
		if (stat(cmd->fullpath, &statbuf) == ERR)
			exit(error_exec(cmd->fullpath, ENOENT) + 1 + g_sh.last_return);
		if (S_ISDIR(statbuf.st_mode))
			exit(error_exec(cmd->fullpath, EISDIR) + 1 + g_sh.last_return);
		if (access(cmd->fullpath, X_OK) == ERR)
			exit(error_exec(cmd->fullpath, EACCES) + 1 + g_sh.last_return);
	}
	execve(cmd->fullpath, args, env);
	error_exec(args[0], errno);
	exit(g_sh.last_return);
}

int	exec_cmd(t_command *cmd, char **env)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		return (error_stdfunc("fork"));
	if (pid)
		close_unused_pipes(cmd->redirects);
	else
		cmd_child_routine(cmd, env);
	return (pid);
}

int	try_exec(t_list *cmd_lst, char **env, t_list **env_lst, pid_t *pids)
{
	t_command	*cmd;
	int			i;
	int			size;

	size = ft_lstsize(cmd_lst);
	i = 0;
	while (cmd_lst)
	{
		cmd = (t_command *)cmd_lst->content;
		if (!cmd->words)
		{
			pids[i] = 0;
			close_unused_pipes(cmd->redirects);
		}
		else if (cmd->builtin && size > 1)
			pids[i] = exec_builtin_pipe(cmd, env_lst);
		else if (cmd->builtin)
			pids[i] = exec_builtin(cmd, env_lst);
		else
			pids[i] = exec_cmd(cmd, env);
		if (pids[i++] == ERR)
			return (ERR);
		cmd_lst = cmd_lst->next;
	}
	return (OK);
}

int	wait_cmds(pid_t *pids, int size)
{
	int	statloc;
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &statloc, 0);
			if (WIFSIGNALED(statloc) && WTERMSIG(statloc) == SIGPIPE)
				continue ;
			else if (WIFSIGNALED(statloc))
				return (error_sig(WTERMSIG(statloc)));
			if (statloc > 2 && statloc < 126)
				g_sh.last_return = !!statloc;
			else
				g_sh.last_return = statloc % MAX_EXITCODE;
		}
		else
			g_sh.last_return = pids[i];
	}
	return (OK);
}

int	exec(t_list *cmd_lst, t_list **env_lst)
{
	pid_t		*pids;
	char		**env;

	signal(SIGQUIT, signal_quit);
	g_sh.status = SH_EXEC;
	pids = malloc(sizeof(pid_t) * ft_lstsize(cmd_lst));
	if (!pids)
		return (error_stdfunc("malloc"));
	if (init_arrlst(*env_lst, &env, TRUE) == ERR)
		return (free_simple(pids, 0, ERR));
	if (try_exec(cmd_lst, env, env_lst, pids) == ERR)
	{
		free_simple(pids, 0, ERR);
		return (free_2d(env, ERR));
	}
	if (wait_cmds(pids, ft_lstsize(cmd_lst)) == ERR)
	{
		free_simple(pids, 0, ERR);
		return (free_2d(env, ERR));
	}
	g_sh.status = SH_DEFAULT;
	free(pids);
	return (free_2d(env, OK));
}

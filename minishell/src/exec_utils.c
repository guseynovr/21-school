/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:25:12 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 13:32:08 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_arrlst(t_list *lst, char ***arr, int is_dict)
{
	int		i;

	*arr = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!*arr)
		return (error_stdfunc("malloc"));
	(*arr)[ft_lstsize(lst)] = NULL;
	i = 0;
	while (lst)
	{
		if (is_dict)
			(*arr)[i] = strjoin3(((t_dict *)lst->content)->key, "=",
					((t_dict *)lst->content)->value);
		else
			(*arr)[i] = ft_strdup((char *)lst->content);
		if (!(*arr)[i])
		{
			free_2d(*arr, ERR);
			return (error_stdfunc("malloc"));
		}
		lst = lst->next;
		i++;
	}
	return (OK);
}

void	close_unused_pipes(t_redirect *r)
{
	while (r)
	{
		close(r->redirectee.fd);
		r = r->next;
	}
}

int	exec_builtin(t_command *cmd, t_list **env_lst)
{
	int		stdin;
	int		stdout;
	char	**args;

	if (init_arrlst(cmd->words, &args, FALSE) == ERR)
		return (ERR);
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (stdin < 0 || stdout < 0)
		return (error_stdfunc("dup") + 1 + free_2d(args, ERR));
	if (redirect(cmd->redirects) == ERR)
		return (free_2d(args, ERR));
	if (cmd->builtin(ft_lstsize(cmd->words), args, env_lst) == ERR)
	{
		if (dup2(stdin, STDIN_FILENO) < 0 || dup2(stdout, STDOUT_FILENO) < 0)
			error_stdfunc("dup2");
		return (free_2d(args, ERR));
	}
	if (dup2(stdin, STDIN_FILENO) < 0 || dup2(stdout, STDOUT_FILENO) < 0)
		return (error_stdfunc("dup2") + 1 + free_2d(args, ERR));
	return (OK);
}

int	exec_builtin_pipe(t_command *cmd, t_list **env_lst)
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid < 0)
		return (error_stdfunc("fork"));
	if (pid)
		close_unused_pipes(cmd->redirects);
	else
	{
		if (redirect(cmd->redirects) == ERR)
			exit(g_sh.last_return);
		if (!cmd->words)
			exit(OK);
		if (init_arrlst(cmd->words, &args, FALSE) == ERR)
			exit(g_sh.last_return);
		cmd->builtin(ft_lstsize(cmd->words), args, env_lst);
		exit(g_sh.last_return);
	}
	return (pid);
}

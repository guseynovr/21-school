/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 14:24:57 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 18:33:25 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* func for execution part after forking */
int	redirect(t_redirect *r)
{
	while (r)
	{
		if (r->type == R_PIPEIN || r->type == R_PIPEOUT)
		{
			close(r->redirector);
			r->redirector = r->type - 1;
		}
		if (r->type == R_HERE)
			r->redirector = 0;
		if (dup2(r->redirectee.fd, r->redirector) < 0)
			return (error_stdfunc("dup2"));
		r = r->next;
	}
	return (OK);
}

int	prepare_pipe(t_redirect *r, int *fds)
{
	if (r->type == R_PIPEOUT && pipe(fds) < 0)
		return (error_stdfunc("pipe"));
	if (r->type == R_PIPEIN)
	{
		r->redirector = fds[1];
		r->redirectee.fd = fds[0];
	}
	else if (r->type == R_PIPEOUT)
	{
		r->redirector = fds[0];
		r->redirectee.fd = fds[1];
	}
	return (OK);
}

int	prepare_heredoc(t_redirect *r, t_list *env_lst)
{
	int		fds[2];

	if (pipe(fds) < 0)
		return (error_stdfunc("pipe"));
	r->redirector = fds[1];
	r->redirectee.fd = fds[0];
	signal(SIGINT, signal_heredoc);
	rl_event_hook = event;
	start_heredoc(r->here_doc_eof, fds, env_lst);
	rl_done = 0;
	if (g_sh.status == SH_HEREDOC)
	{
		g_sh.status = SH_DEFAULT;
		return (ERR);
	}
	signal(SIGINT, sig_hand_main);
	return (close (fds[1]) + OK);
}

int	prepare_default(t_redirect *r)
{
	int		ret;

	ret = open(r->redirectee.filename, r->flags, 0644);
	if (ret < 0)
	{
		error_stdfunc(r->redirectee.filename);
		free(r->redirectee.filename);
		return (ERR);
	}
	free(r->redirectee.filename);
	r->redirectee.fd = ret;
	return (OK);
}

int	prepare_redirects(t_list *cmd_lst, t_list *env_lst)
{
	t_redirect	*r;
	int			pipe[2];
	int			ret;

	while (cmd_lst)
	{
		r = (t_redirect *)((t_command *) cmd_lst->content)->redirects;
		while (r)
		{
			if (r->type == R_DEFAULT)
				ret = prepare_default(r);
			else if (r->type == R_PIPEIN || r->type == R_PIPEOUT)
				ret = prepare_pipe(r, pipe);
			else if (r->type == R_HERE)
				ret = prepare_heredoc(r, env_lst);
			if (ret == ERR)
				return (ERR);
			r = r->next;
		}
		cmd_lst = cmd_lst->next;
	}
	return (OK);
}

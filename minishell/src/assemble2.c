/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 14:21:27 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 20:30:28 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_cmd(t_command **next_cmd, t_list **next_lst)
{
	*next_cmd = malloc(sizeof(t_command));
	if (!*next_cmd)
		return (error_stdfunc("malloc"));
	ft_bzero(*next_cmd, sizeof(t_command));
	*next_lst = ft_lstnew(*next_cmd);
	if (!*next_lst)
	{
		free(*next_cmd);
		return (error_stdfunc("malloc"));
	}
	return (OK);
}

void	_assemble_redirect(t_redirect *redirect, char *s)
{
	if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0)
		redirect->redirector = 1;
	if (ft_strcmp(s, ">") == 0)
		redirect->flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (ft_strcmp(s, ">>") == 0)
		redirect->flags = O_WRONLY | O_CREAT | O_APPEND;
	else if (ft_strcmp(s, "<") == 0)
		redirect->flags = O_RDONLY;
	else if (ft_strcmp(s, "<<") == 0)
		redirect->type = R_HERE;
}

int	assemble_redirect(t_redirect *redirect, t_list **token_lst)
{
	char	*s;

	s = ((t_token *)(*token_lst)->content)->str;
	_assemble_redirect(redirect, s);
	*token_lst = (*token_lst)->next;
	if (!*token_lst)
		return (error_parsing("newline"));
	if (((t_token *)(*token_lst)->content)->type == T_OP)
		return (error_parsing(((t_token *)(*token_lst)->content)->str));
	if (!ft_strcmp(s, "<") || !ft_strcmp(s, ">") || !ft_strcmp(s, ">>"))
	{
		redirect->redirectee.filename = ft_strdup(
				((t_token *)(*token_lst)->content)->str);
		if (!redirect->redirectee.filename)
			return (error_stdfunc("malloc"));
	}
	else if (ft_strcmp(s, "<<") == 0)
	{
		redirect->here_doc_eof = ft_strdup(
				((t_token *)(*token_lst)->content)->str);
		if (!redirect->here_doc_eof)
			return (error_stdfunc("malloc"));
	}
	return (OK);
}

int	add_redirect(t_list **token_lst, t_redirect **redirects, enum e_rtype rt)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (error_stdfunc("malloc"));
	ft_bzero(new, sizeof(t_redirect));
	if (rt == R_DEFAULT || rt == R_HERE)
	{
		if (assemble_redirect(new, token_lst) == ERR)
			return (free_simple(new, 0, ERR));
		redirectadd_back(redirects, new);
	}
	else if (rt == R_PIPEIN || rt == R_PIPEOUT)
	{
		new->type = rt;
		new->redirector = rt - 1;
		if (rt == R_PIPEOUT && *redirects && (*redirects)->type == R_PIPEIN)
		{
			new->next = (*redirects)->next;
			(*redirects)->next = new;
		}
		else
			redirectadd_front(redirects, new);
	}
	return (OK);
}

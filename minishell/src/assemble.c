/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:46:51 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 20:30:50 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_word(t_token *token, t_list **words, t_list *env_lst)
{
	t_list	*new;
	char	*str;

	str = ft_strdup(token->str);
	if (!str)
		return (error_stdfunc("malloc"));
	new = ft_lstnew(str);
	if (!new)
	{
		free(str);
		return (error_stdfunc("malloc"));
	}
	if (!is_empty_var(str, env_lst))
		ft_lstadd_back(words, new);
	else
		free_simple(str, new, OK);
	return (OK);
}

int	assmble_until_f(t_list **token_lst, t_list **next_lst, t_command *next_cmd,
t_list *env_lst)
{
	int	ret;

	while (*token_lst && !is_op(((t_token *)(*token_lst)->content)->str,
		CTRL_OP, ft_strlen(((t_token *)(*token_lst)->content)->str)))
	{
		if (((t_token *)(*token_lst)->content)->type == T_WORD)
			ret = add_word(((t_token *)(*token_lst)->content),
					&next_cmd->words, env_lst);
		else
			ret = add_redirect(token_lst, &next_cmd->redirects, R_DEFAULT);
		if (ret == ERR)
		{
			del_cmd(next_cmd);
			return (free_simple(0, *next_lst, ERR));
		}
		*token_lst = (*token_lst)->next;
	}
	return (OK);
}

int	assemble_last(t_list **token_lst, t_command	*next_cmd,
	t_list **next_lst, int *pipe_in)
{
	if (*token_lst && is_op(((t_token *)(*token_lst)->content)->str,
		CTRL_OP, ft_strlen(((t_token *)(*token_lst)->content)->str)))
	{
		if (add_redirect(token_lst, &next_cmd->redirects, R_PIPEOUT) == ERR)
		{
			del_cmd(next_cmd);
			return (free_simple(0, *next_lst, ERR));
		}
		next_cmd->ctrl_op = CO_PIPE;
		*token_lst = (*token_lst)->next;
		if (*token_lst)
			*pipe_in = TRUE;
		else
		{
			*pipe_in = FALSE;
			del_cmd(next_cmd);
			free_simple(0, *next_lst, ERR);
			return (error_parsing("newline"));
		}
	}
	else
		*pipe_in = FALSE;
	return (OK);
}

int	next_cmd(t_list **token_lst, t_list **next_lst, t_list *env_lst)
{
	t_command	*next_cmd;
	static int	pipe_in;

	if (!*token_lst)
		return (END);
	if (is_op(((t_token *)(*token_lst)->content)->str, CTRL_OP,
		ft_strlen(((t_token *)(*token_lst)->content)->str)))
		return (error_parsing(((t_token *)(*token_lst)->content)->str));
	if (malloc_cmd(&next_cmd, next_lst) == ERR)
		return (error_stdfunc("malloc"));
	if (pipe_in
		&& add_redirect(token_lst, &next_cmd->redirects, R_PIPEIN) == ERR)
		return (free_simple(next_cmd, *next_lst, ERR));
	if (assmble_until_f(token_lst, next_lst, next_cmd, env_lst) == ERR)
		return (ERR);
	if (assemble_last(token_lst, next_cmd, next_lst, &pipe_in) == ERR)
		return (ERR);
	return (OK);
}

int	assemble(t_list	*token_lst, t_list **cmd_lst, t_list *env_lst)
{
	t_list		*next_lst;
	int			ret;

	*cmd_lst = 0;
	ret = next_cmd(&token_lst, &next_lst, env_lst);
	while (ret == OK)
	{
		ft_lstadd_back(cmd_lst, next_lst);
		ret = next_cmd(&token_lst, &next_lst, env_lst);
	}
	if (ret == ERR)
	{
		ft_lstclear(cmd_lst, del_cmd);
		return (ERR);
	}
	return (OK);
}

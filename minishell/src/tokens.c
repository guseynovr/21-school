/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:48:09 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/02 18:07:57 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_token(t_token **next_tkn, t_list **next_lst)
{
	*next_tkn = malloc(sizeof(t_token));
	if (!*next_tkn)
		return (ERR);
	ft_bzero(*next_tkn, sizeof(t_token));
	*next_lst = ft_lstnew(*next_tkn);
	if (!*next_lst)
	{
		free(*next_tkn);
		return (ERR);
	}
	return (OK);
}

/*
Apply POSIX tokenization rules to a character
return:
	TKN_OK:		token boundary reached
	TKN_EMPTY:	unquoted <blank> found
	TKN_END:	end of string reached
	TKN_CNTN:	token end not reached, keep parsing
*/
int	check_char(char *s, int len, int *qtype, t_token *tkn)
{
	if (!s[len] && len > 0)
		return (TKN_OK);
	else if (!s[len])
		return (TKN_END);
	else if (tkn->type == T_OP && *qtype == 0 && is_op(s, OPERATORS, len + 1))
		return (TKN_CNTN);
	else if (tkn->type == T_OP && !is_op(s, OPERATORS, len + 1))
		return (TKN_OK);
	else if ((s[len] == '\'' || s[len] == '\"') && *qtype == Q_NONE)
		*qtype = s[len];
	else if ((s[len] == '\'' || s[len] == '\"') && *qtype == s[len])
		*qtype = Q_NONE;
	else if (*qtype == Q_NONE && ft_strchr(OP_SYM, s[len]) && len > 0)
		return (TKN_OK);
	else if (*qtype == Q_NONE && ft_strchr(OP_SYM, s[len]))
		tkn->type = T_OP;
	else if (*qtype == Q_NONE && ft_strchr(IFS, s[len]) && len > 0)
		return (TKN_OK);
	else if (*qtype == Q_NONE && ft_strchr(IFS, s[len]))
		return (TKN_EMPTY);
	else
		tkn->type = T_WORD;
	return (TKN_CNTN);
}

/*
Find the boundary of the next token and set its type
return:
	TKN_OK:		successfully found a token
	TKN_EMPTY:	token is empty and have to be discarded
	TKN_END:	no more tokens available
	ERR:		syntax error - open quotes
*/
int	parse_next(char *s, int *len, t_token *tkn)
{
	int	qtype;
	int	ret;

	if (!*s)
		return (TKN_END);
	*len = 0;
	ret = TKN_CNTN;
	qtype = Q_NONE;
	tkn->type = 0;
	while (ret == TKN_CNTN)
	{
		ret = check_char(s, *len, &qtype, tkn);
		if (ret != TKN_OK)
			(*len)++;
	}
	if (ret == TKN_END || qtype)
	{
		printf(SH_NAME ": unexpected EOF while looking for matching `%c'\n",
			qtype);
		return (ERR);
	}
	return (ret);
}

/*
return: 
	OK:		`next_lst` has correct and allocated element of list 
			with a token as `content`
	ERR:	some system error happened (eg. malloc error),
			cant't continue to excecute
	END:	successfully finished searching for tokens
	ERR:	found syntax error
*/
int	next_token(char **s, t_list **next_lst)
{
	int			len;
	int			ret;
	t_token		*next_tkn;

	if (!*s)
		return (END);
	if (malloc_token(&next_tkn, next_lst) == ERR)
		return (ERR);
	ret = parse_next(*s, &len, next_tkn);
	while (ret == TKN_EMPTY)
		ret = parse_next(++(*s), &len, next_tkn);
	if (ret == TKN_END || ret == ERR)
		return (ret);
	next_tkn->str = ft_substr(*s, 0, len);
	if (!next_tkn->str)
	{
		free(next_tkn);
		free(*next_lst);
		return (ERR);
	}
	(*s) += len;
	return (OK);
}

/*  */
int	get_tokens(char *s, t_list **token_lst)
{
	t_list	*next_lst;
	int		ret;

	*token_lst = 0;
	ret = next_token(&s, &next_lst);
	while (ret == OK)
	{
		ft_lstadd_back(token_lst, next_lst);
		ret = next_token(&s, &next_lst);
	}
	if (ret == ERR)
	{
		ft_lstclear(token_lst, del_token);
		return (ERR);
	}
	return (OK);
}

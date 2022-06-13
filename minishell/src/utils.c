/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:15:56 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 15:49:55 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_token(void *p)
{
	t_token	*token;

	if (!p)
		return ;
	token = (t_token *) p;
	free(token->str);
	free(token);
}

void	del_cmd(void *p)
{
	t_command	*cmd;
	t_redirect	*redirect;
	t_redirect	*tmp_redirect;

	if (!p)
		return ;
	cmd = (t_command *) p;
	ft_lstclear(&cmd->words, free);
	redirect = cmd->redirects;
	while (redirect)
	{
		tmp_redirect = redirect;
		redirect = redirect->next;
		free(tmp_redirect->here_doc_eof);
		free(tmp_redirect);
	}
	free(cmd);
}

int	is_op(char *s, char *ops, int len)
{
	int	cmp_len;

	cmp_len = 0;
	while (1)
	{
		if ((!*ops || *ops == ' ') && cmp_len == len)
			return (1);
		else if (!*ops && cmp_len != len)
			return (0);
		else if ((*ops == ' ' && cmp_len != len) || (*ops != s[cmp_len]))
		{
			ops = strchr(ops, ' ');
			if (!ops++)
				return (0);
			cmp_len = 0;
		}
		else if (*ops == s[cmp_len])
		{
			ops++;
			cmp_len++;
		}
		else
			return (0);
	}
}

char	*strjoin3(char *s1, char *s2, char *s3)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	if (!tmp)
		return (NULL);
	free(tmp);
	return (result);
}

int	is_validname(char *name)
{
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (FALSE);
		name++;
	}
	return (TRUE);
}

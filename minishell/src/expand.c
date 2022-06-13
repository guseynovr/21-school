/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:33:20 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 15:36:20 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_full_path(t_list *env, t_command *cmd)
{
	char	*fullpath;
	char	**paths;
	int		ret;

	if (get_arr_paths(env, &paths) == ERR)
		return (ERR);
	else if (!paths)
	{
		cmd->fullpath = cmd->words->content;
		return (0);
	}
	if (*((char *)cmd->words->content))
	{
		ret = check_paths(&fullpath, paths, cmd);
		if (ret != END)
			return (ret);
	}
	cmd->fullpath = cmd->words->content;
	return (free_2d(paths, OK));
}

int	first_word(t_command *cmd, t_list *env)
{
	if (expand_word((char **)&cmd->words->content, env) == ERR)
		return (ERR);
	if (is_path_specified(cmd->words->content))
	{
		cmd->fullpath = cmd->words->content;
		return (0);
	}
	cmd->builtin = get_builtin(cmd->words->content);
	if (cmd->builtin)
		return (0);
	if (find_full_path(env, cmd) == ERR)
		return (ERR);
	return (0);
}

int	expand_words(t_command *cmd, t_list *env)
{
	t_list		*tmp;

	if (first_word(cmd, env) == ERR)
		return (ERR);
	tmp = cmd->words;
	tmp = tmp->next;
	while (tmp)
	{
		if (expand_word((char **)&tmp->content, env) == ERR)
			return (ERR);
		tmp = tmp->next;
	}
	return (OK);
}

int	expand(t_command *cmd, t_list *env)
{
	t_redirect	*r_tmp;

	if (cmd->words && expand_words(cmd, env) == ERR)
		return (ERR);
	r_tmp = cmd->redirects;
	while (r_tmp)
	{
		if (r_tmp->type == R_DEFAULT)
			if (expand_word(&r_tmp->redirectee.filename, env) == ERR)
				return (ERR);
		r_tmp = r_tmp->next;
	}
	r_tmp = cmd->redirects;
	if (r_tmp && r_tmp->type == R_HERE
		&& expand_key_heredoc(&r_tmp->here_doc_eof) == ERR)
		return (ERR);
	return (0);
}

int	expansion(t_list *comands, t_list *env)
{
	t_list	*tmp;

	tmp = comands;
	while (tmp)
	{
		if (expand((t_command *)tmp->content, env) == ERR)
			return (ERR);
		tmp = tmp->next;
	}
	return (0);
}

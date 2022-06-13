/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:37:34 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 18:58:33 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arr_paths(t_list *env, char ***paths)
{
	t_dict	*pth;

	*paths = 0;
	pth = get_var("PATH", env);
	if (!pth)
		return (0);
	*paths = ft_split(pth->value, ':');
	if (!*paths)
		return (ERR);
	return (OK);
}

int	(*get_builtin(char *s))(int c, char **v, t_list **e_l)
{
	const t_builtin_func	funcs[7] = {
		echo, cd, pwd, export, unset, env, mexit};
	const char				*func_names[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int						i;

	i = -1;
	while (++i < 7)
	{
		if (!ft_strcmp(s, func_names[i]))
			return (funcs[i]);
	}
	return (NULL);
}

int	check_paths(char **fullpath, char **paths, t_command *cmd)
{
	int	i;

	i = -1;
	while (paths[++i])
	{
		*fullpath = strjoin3(paths[i], "/", cmd->words->content);
		if (!*fullpath)
			return (free_2d(paths, ERR));
		if (!access(*fullpath, X_OK))
		{
			cmd->fullpath = *fullpath;
			return (free_2d(paths, OK));
		}
		free(*fullpath);
	}
	return (END);
}

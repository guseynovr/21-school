/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:22:15 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 13:46:02 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_cd(char *path, t_list **env_lst)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (error_stdfunc("cwd"));
	if (set_var("OLDPWD", cwd, env_lst) == ERR)
	{
		free(cwd);
		return (error_stdfunc("malloc"));
	}
	if (chdir(path) == ERR)
	{
		free(cwd);
		return (error_builtin(path, "cd"));
	}
	cwd = getcwd(0, 0);
	if (!cwd)
		return (error_stdfunc("cwd"));
	if (set_var("PWD", cwd, env_lst) == ERR)
	{
		free(cwd);
		return (error_stdfunc("malloc"));
	}
	return (OK);
}

int	cd(int argc, char **argv, t_list **env_lst)
{
	t_dict	*dict;
	char	*path;

	if (argc < 2)
	{
		dict = get_var("HOME", *env_lst);
		if (!dict)
			return (error_custom(1, "cd", "HOME not set"));
		path = dict->value;
	}
	else
		path = argv[1];
	return (_cd(path, env_lst));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 20:20:06 by dgidget           #+#    #+#             */
/*   Updated: 2021/09/23 12:11:34 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int argc, char **argv, t_list **env_lst)
{
	char	*cwd;

	(void) argc;
	(void) argv;
	(void) env_lst;
	cwd = getcwd(0, 0);
	if (!cwd)
		return (error_stdfunc("pwd"));
	printf("%s\n", cwd);
	free(cwd);
	return (OK);
}

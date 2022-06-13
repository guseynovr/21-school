/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:30:51 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 16:44:11 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_builtin(char *err_subject, char *builtin)
{
	ft_putstr_fd(SH_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_subject, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (ERR);
}

int	error_exec(char *cmd_name, int status)
{
	ft_putstr_fd(SH_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (status == 2)
	{
		g_sh.last_return = 127;
		ft_putendl_fd("command not found", STDERR_FILENO);
	}
	else
	{
		g_sh.last_return = 126;
		ft_putendl_fd(strerror(status), STDERR_FILENO);
	}
	return (ERR);
}

int	free_simple(void *p1, void *p2, int status)
{
	free(p1);
	free(p2);
	return (status);
}

/* Deallocate two-dimensional null terminated array */
int	free_2d(char **p, int status)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
	return (status);
}

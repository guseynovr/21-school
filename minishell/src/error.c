/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:12:34 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 15:31:44 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_signal.h"
#include "minishell.h"

int	error_sig(int signal)
{
	const char	*strs[SIGSTRS_COUNT] =
	{
		SIG_0, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7, SIG_8, SIG_9,
		SIG_10, SIG_11, SIG_12, SIG_13, SIG_14, SIG_15, SIG_16, SIG_17, SIG_18,
		SIG_19, SIG_20, SIG_21, SIG_22, SIG_23, SIG_24, SIG_25, SIG_26, SIG_27,
		SIG_28, SIG_29, SIG_30, SIG_31
	};

	g_sh.last_return = (128 + signal) % MAX_EXITCODE;
	if (signal < 1 || signal > 31)
	{
		ft_putstr_fd((char *)strs[0], STDERR_FILENO);
		ft_putchar_fd(' ', STDERR_FILENO);
		ft_putnbr_fd(signal, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (signal != 2)
		ft_putstr_fd((char *)strs[signal], STDERR_FILENO);
	return (ERR);
}

int	error_parsing(char *token_str)
{
	ft_putstr_fd(SH_NAME, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token_str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (ERR);
}

int	error_export(char *builtin, char *err_subject)
{
	g_sh.last_return = 1;
	ft_putstr_fd(SH_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(err_subject, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (ERR);
}

int	error_custom(int status, char *prefix, char *err_str)
{
	g_sh.last_return = status;
	ft_putstr_fd(SH_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err_str, STDERR_FILENO);
	return (ERR);
}

int	error_stdfunc(char *err_subject)
{
	g_sh.last_return = !!errno;
	ft_putstr_fd(SH_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_subject, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (ERR);
}

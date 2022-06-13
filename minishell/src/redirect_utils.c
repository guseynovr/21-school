/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:31:57 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 18:32:14 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_heredoc(char *here_doc_eof, int *fds, t_list *env_lst)
{
	char	*s;

	while (TRUE)
	{
		s = readline(">");
		if (g_sh.status == SH_HEREDOC || !s || !ft_strcmp(s, here_doc_eof))
			break ;
		if (expand_word_heredoc(&s, env_lst) == ERR)
		{
			free(s);
			close(fds[0]);
			close(fds[1]);
			return (error_stdfunc("malloc"));
		}
		ft_putendl_fd(s, fds[1]);
		free(s);
	}
	free(s);
	return (OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:57 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 20:22:48 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	print_tokenlst(t_list *token_lst)
{
	printf("TOKENS\n");
	while (token_lst)
	{
		t_token *tkn = (t_token *) token_lst->content;
		printf("type = %i, str = (%s)\n", tkn->type, tkn->str);
		token_lst = token_lst->next;
	}
	printf("\n");
}

void	print_word(void *word) { printf("%s ", (char *)word); }

void	print_cmd(void *cmd_p)
{
	t_command	*cmd;
	t_redirect	*redirect;
	
	cmd = (t_command *) cmd_p;
	redirect = (t_redirect *) cmd->redirects;
	printf("Words: ");
	ft_lstiter(cmd->words, print_word);
	printf("\n");
	while (redirect)
	{
		printf("Redirect: type = %i, redirector = %i, redirectee.fd = %i, "
			"here_doc_eof = %s\n", redirect->type, redirect->redirector,
			redirect->redirectee.fd,
			redirect->here_doc_eof);
		printf("next = %p\n", redirect->next);
		redirect = redirect->next;
	}
	printf("Ctrl_op: %i\n\n", cmd->ctrl_op);
}

void	print_fds_status(char *s)
{
	int	i;

	printf("%-15s ", s);
	i = -1;
	while (++i < 15)
		printf("fd%i: status: %i; ", i, fcntl(i, F_GETFL) != -1 || errno != EBADF);
	printf("\n");
} */

int	parse(char *read_str, t_list **token_lst, t_list **cmd_lst, t_list *env_lst)
{
	int	ret;

	ret = get_tokens(read_str, token_lst);
	free(read_str);
	if (ret == ERR)
		return (ERR);
	ret = assemble(*token_lst, cmd_lst, env_lst);
	ft_lstclear(token_lst, del_token);
	if (ret == ERR)
		return (ERR);
	return (OK);
}

int	perform_expansion(t_list **cmd_lst, t_list **env_lst)
{
	if (expansion(*cmd_lst, *env_lst) == ERR)
	{
		ft_lstclear(cmd_lst, del_cmd);
		return (ERR);
	}
	if (prepare_redirects(*cmd_lst, *env_lst) == ERR)
	{
		ft_lstclear(cmd_lst, del_cmd);
		return (ERR);
	}
	return (OK);
}

int	execute(t_list **cmd_lst, t_list **env_lst)
{
	int	ret;

	ret = exec(*cmd_lst, env_lst);
	ft_lstclear(cmd_lst, del_cmd);
	if (ret == ERR)
		return (ERR);
	return (OK);
}

int	get_input_line(char **read_str)
{
	*read_str = readline(SH_NAME "$ ");
	if (!*read_str)
		my_exit(SH_NAME);
	if (!**read_str)
	{
		free(*read_str);
		return (ERR);
	}
	add_history(*read_str);
	return (OK);
}

int	main(int argc, char **argv, char **env)
{
	char	*read_str;
	t_list	*token_lst;
	t_list	*cmd_lst;
	t_list	*env_lst;

	(void) argc;
	(void) argv;
	env_lst = init_env(env);
	if (!env_lst)
		return (error_stdfunc("malloc") + 1 + g_sh.last_return);
	while (TRUE)
	{
		signal(SIGINT, sig_hand_main);
		signal(SIGQUIT, sig_hand_main);
		if (get_input_line(&read_str) == ERR
			|| parse(read_str, &token_lst, &cmd_lst, env_lst) == ERR
			|| perform_expansion(&cmd_lst, &env_lst) == ERR
			|| execute(&cmd_lst, &env_lst) == ERR)
			continue ;
	}
	ft_lstclear(&env_lst, clear_dict);
	// rl_clear_history();
	return (g_sh.last_return);
}

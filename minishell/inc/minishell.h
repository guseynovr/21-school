/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:10:13 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 20:23:41 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE			1
# define FALSE			0

# define SH_NAME		"minishell"

/* Global return codes */
# define OK				0
# define ERR			-1
# define END			-2

# define Q_NONE			0
# define Q_SINGLE		'\''
# define Q_DOUBLE		'\"'

# define METACHARACTERS "|$<>\n \t" //NOT USED
# define IFS			" \t\n"
# define OP_SYM			"<>|"
# define OPERATORS		"< << > >> |"
# define CTRL_OP		"|"
# define RDRCT_OP		"< << > >>" //NOT USED

# define CE_AMBRED		"ambiguous redirect" //NOT USED

# define MAX_EXITCODE	255

/* Token recognision codes */
enum	e_tkn {TKN_OK, TKN_EMPTY, TKN_END, TKN_CNTN};

/* Token types */
enum	e_tkntype {T_WORD, T_OP};

/* Redirect types */
enum	e_rtype {R_DEFAULT, R_PIPEIN, R_PIPEOUT, R_HERE};

/* Control operator types */
enum	e_co {CO_NULL, CO_PIPE, CO_AND, CO_OR};

/* Shell statuses */
enum	e_sh {SH_DEFAULT, SH_HEREDOC, SH_EXEC};

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

typedef union u_redirectee {
	int		fd;
	char	*filename;
}	t_redirectee;

typedef struct s_redirect
{
	struct s_redirect	*next;
	int					type;
	int					flags;
	int					redirector;
	t_redirectee		redirectee;
	char				*here_doc_eof;
}	t_redirect;

typedef struct s_exp
{
	char	*word;
	int		i;
	t_list	**lst;
}	t_exp;

typedef struct s_command
{
	t_list		*words;
	t_redirect	*redirects;
	char		*fullpath;
	int			(*builtin)(int argc, char **argv, t_list **env_lst);
	int			ctrl_op;
}	t_command;

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

typedef struct s_shell
{
	int	status;
	int	last_return;
}	t_shell;

typedef int	(*t_builtin_func)(int, char **, t_list **);

t_shell		g_sh;

/* Parsing */
int		get_tokens(char *s, t_list **tokens);
int		assemble(t_list *token_lst, t_list **cmd_lst, t_list *env_lst);

/* Assemble utils */
int		malloc_cmd(t_command **next_cmd, t_list **next_lst);
int		add_redirect(t_list **tkn_lst, t_redirect **redirects, enum e_rtype rt);

/* Assemble utils */
void	redirectadd_back(t_redirect **redirects, t_redirect *new);
void	redirectadd_front(t_redirect **redirects, t_redirect *new);
int		is_empty_var(char *str, t_list *env_lst);

/* Expansion and redirection */
int		prepare_redirects(t_list *cmd_lst, t_list *env_lst);
int		redirect(t_redirect *r);
int		start_heredoc(char *here_doc_eof, int *fds, t_list *env_lst);

/* Executing */
int		exec(t_list *cmd_lst, t_list **env_lst);

/* Exec utils */
int		init_arrlst(t_list *lst, char ***arr, int is_dict);
void	close_unused_pipes(t_redirect *r);
int		exec_builtin(t_command *cmd, t_list **env_lst);
int		exec_builtin_pipe(t_command *cmd, t_list **env_lst);

/* Working with env */
t_list	*init_env(char **raw_env);
t_dict	*get_var(char *key, t_list *lst);
int		set_var(char *key, char *value, t_list **lst);
void	del_var(char *key, t_list **lst);
int		set_shelllvl(t_list **env);

/* Parse env utils */
t_dict	*str_to_dict(char *key, char *value);
t_dict	*arr_to_dict(char *str);

/* Builtins */
int		echo(int argc, char **argv, t_list **env_lst);
int		cd(int argc, char **argv, t_list **env_lst);
int		pwd(int argc, char **argv, t_list **env_lst);
int		export(int argc, char **argv, t_list **env_lst);
int		unset(int argc, char **argv, t_list **env_lst);
int		env(int argc, char **argv, t_list **env_lst);
int		mexit(int argc, char **argv, t_list **env_lst);

/* Utils */
void	del_token(void *p);
void	del_cmd(void *p);
int		is_op(char *s, char *ops, int len);
char	*strjoin3(char *s1, char *s2, char *s3);
int		is_validname(char *name);
char	*get_key(char *s);
char	*get_value(char *s);
void	print_env_lst(void *p);
int		is_path_specified(char *s);
void	clear_dict(void *del_node);
void	print_env_lst(void *p);

/* Expand */
int		expansion(t_list *comands, t_list *env);
int		expand_single_quote(t_exp *exp);
int		expand_var_in_q(char *str, t_list *env, t_exp *exp, int *i);
int		setting_var(char **inner, t_list *env, t_exp *exp);
int		expand_double_quote(t_exp *exp, t_list *env);
int		ft_len_content(t_list *lst);
int		empty_dollar(t_exp *exp, t_list **l_tmp);
int		expand_var(t_list *env, t_exp *exp);
int		init_exp(t_exp **exp, char *word);
int		ft_lstjoin(t_list **lst, char **word);
int		expand_word(char **word, t_list *env);
int		expand_word_heredoc(char **word, t_list *env);
int		expand_s_quote_heredoc(t_exp *exp, t_list *env);
int		expand_key_heredoc(char **word);
int		clr_exp(t_exp *exp, int status);
int		get_arr_paths(t_list *env, char ***paths);
int		(*get_builtin(char *s))(int, char **, t_list **);
int		check_paths(char **fullpath, char **paths, t_command *cmd);
int		init_sym(char *tmp, int i, t_exp *exp);
int		dollar_answ_in_q(t_exp *exp, char *s, int *i);

/* Debug utils */
void	print_tokenlst(t_list	*token_lst);
void	print_fds_status(char *s);

/* Signals */
void	sig_hand_too(int signal);
void	sig_hand_main(int signal);
void	my_exit(char *welc);
void	signal_quit(int signal);
void	my_heredoc(char *welc);
void	signal_heredoc(int signal);
int		event(void);

/* Error handling */
int		error_sig(int signal);
int		error_parsing(char *token_str);
int		error_custom(int code, char *prefix, char *err_str);
int		error_stdfunc(char *err_subject);
int		error_exec(char *cmd_name, int status);
int		error_builtin(char *err_subject, char *builtin);
int		error_export(char *builtin, char *err_subject);
int		free_simple(void *p1, void *p2, int status);
int		free_2d(char **p, int status);

#endif

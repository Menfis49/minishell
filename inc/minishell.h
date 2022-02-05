/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:21:05 by jholl             #+#    #+#             */
/*   Updated: 2022/02/03 12:09:32 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>

# define MALLOC_ERROR "Minishell: Malloc:"
# define TMP_FILES "/tmp/sh-thd.here_doc."

extern int	g_exit_status;

enum e_token_type
{
	TOK_LITTERAL = 1,
	TOK_ISSPACE,
	TOK_VAR,
	TOK_LAST_STATUT,
	TOK_DOUBLE_QUOTE,
	TOK_SINGLE_QUOTE,
	TOK_DELIMETER,
	TOK_RED_INPUT,
	TOK_RED_OUTPUT,
	TOK_RED_OUTPUT_APPENDS,
	TOK_PIPE
};

typedef struct s_pipe
{
	int	nb_pipe;
	int	nb_pipe_created;
	int	count;
	int	read;
	int	prev_read;
	int	fd_pipe[2];
	int	prev_fd_pipe[2];
	int	**dpipe_fd;

}	t_pipe;

typedef struct s_red
{
	int		fd_input;
	int		fd_output;
	int		first_input;
	int		first_output;
	int		is_delimeter;
	char	**tmp_files;
	int		delimeter_entry;
	int		tmp_count;
	int		tmp_actual_count;
	int		tmp_cnt_exec;
}	t_red;

typedef struct s_token_man
{
	char				char_token;
	enum e_token_type	type;
}	t_token_man;

typedef struct s_token
{
	enum e_token_type	type;
	char				**s;
}		t_token;

typedef struct s_list
{
	char				*content;
	enum e_token_type	type;
	struct s_list		*next;
}	t_list;

typedef struct s_btree
{
	struct s_token	tok;
	struct s_btree	*right;
	struct s_btree	*left;
}	t_btree;

typedef struct s_data
{
	t_list	*our_env;
	t_pipe	pipe;
	t_red	red;
	t_list	*lexer;
	t_btree	*ast;
	char	*line_read;
	int		stop_delim;
	int		do_exec;
	char	**env;
	int		*pid;
	int		count_pid;
	int		nb_fork;
	char	*pwd;
	char	*old_pwd;
}	t_data;

//signal
void	handle(int sig);

//main
void	reset_ret_data(t_data *data);

//init
void	init(t_data *data);
void	init_first(t_data *data);
int		count_pipe(t_list **lexer, t_data *data);
void	init_dpipe_fd(int cnt_pipe, t_data *data);
int		count_pipe(t_list **lexer, t_data *data);
void	reset_pipe_data(t_data *data);
void	reset_red_data(t_data *data);
void	count_delimeter(t_list **lexer, t_data *data);
void	init_delimiter(t_data *data);
int		count_digit(int i);

//data
void	reset_data(t_data *data);

//ast
void	create_ast(t_btree **ast, t_list **lexer, t_data *data);
void	redirection_exception(t_btree **ast, t_token token, t_data *data);
void	add_litteral(int pos, int count, t_list **lexer, t_data *data);
void	add_operator(t_list *lexer, t_btree **ast, t_data *data);
void	add_to_ast(t_btree **ast, t_token token, t_data *data);
void	set_new_ds(char **new_ds, char **second, char **first);

//exec
void	exec(t_btree **ast, t_data *data);
int		if_redirection_exec(t_btree **ast, t_data *data);
void	if_pipeline_exec(t_btree **ast, t_data *data);
void	if_litteral_exec(t_btree **ast, t_data *data);
char	*access_command(t_data *data, char *path_cmd);
int		treat_file(t_token tok, t_token right_tok, t_data *data);
int		f_open_creat_rdwr_append(char *path);
int		f_open_creat_rdwr_trunc(char *path);
int		f_open_rdonly(char *path);
void	wait_n_close(t_data *data);
void	delimeter_fork(t_data *data, t_btree *ast);
int		first_delimeter(t_data *data, t_btree **ast);
void	dup_pipe(t_data *data);
void	dup_two_pipes(t_data *data);
void	dup_redirection(t_data *data);
void	exec_delimiter(t_btree **ast, t_data *data);
void	wait_delimiter_fork(t_data *data, int pid);
void	read_write_while_delimeter(t_token tok, t_data *data);
void	read_while_delimeter(t_token tok, t_data *data);

//builtin
int		is_builtin(char *built);
void	built_pwd(t_data *data);
int		is_pwd(char *s);
void	built_echo(char **built, t_data *data);
int		is_echo(char *s);
void	built_env(char **built, t_data *data);
int		is_env(char *s);
void	env_only_data(t_data *data);
void	built_cd(char **built, t_data *data);
int		is_cd(char *s);
void	built_unset(t_data *data, char **built);
int		is_unset(char *s);
void	built_export(t_data *data, char **built);
int		is_export(char *s);
void	built_exit(t_data *data, char **ds);
int		is_exit(char *s);

//utils
void	ft_putstr_fd(char *str, int fd);
void	write_error(char *s);

//var
void	get_caller_env(t_data *data, char **env);
void	treat_var(t_list **lexer, t_list **save_lexer, t_data *data);
char	*lf_var(char *var, t_data *data);
char	*get_value_env(t_data *data, char *name);
char	*duplicate_value_env(t_data *data, char *var_name);
void	set_env(t_data *data, char *name, char *value);
int		check_if_var_exist(char *s1, char *s2);
void	modify_existed_var(t_list *tmp, char *value, t_data *data);

//lexing
void	lexing(char *s, t_list **lexer, t_data *data);
int		is_operator(enum e_token_type type);
int		is_redirection(enum e_token_type type);
int		is_pipe(enum e_token_type type);
int		iq(enum e_token_type type);
int		is_isspace(enum e_token_type type);
void	regroup_token(t_list *lexer, t_data *data);
void	reverse_order_pipe_lexer(t_list **lexer, t_data *data);
int		token_man_set_type(int i);
int		token_man_set_char(int i);
void	delete_isspaces_token(t_list **lexer);

//parsing
int		parsing(t_data *data, t_list **lexer);
void	pars_quotes(t_list **lexer, t_list **save_lexer, t_data *data, int dq);
int		pars_operator(t_list *lexer);
int		pars_what_follows_operator(t_list *lexer, int *pipe);
void	pars_special_case(t_data *data);

//ft_str
char	*ft_strnstr(char *big, char *little, size_t len);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_nb_str(char **content);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strlcat(char *dst, const char *src, int size);
int		ft_strlcpy(char *dst, const char *src, int size);
int		ft_is_alpha(char c);
char	*ft_itoa(int n, t_data *data);
int		ft_atoi(char *nptr);

//ft_lst
t_list	*ft_lstnew(char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstdel_char(t_list *lst, void (del)(char *));
void	ft_lst_delone(t_list **list, t_list *to_del);
void	free_str(char *s);
void	free_dstr(char **s);
t_list	*ft_list_find(t_list *list_start, void *data_ref, int (*cmp)());

//ft_btree
void	del_btree(t_btree **btree, t_data *data);
t_btree	*new_btree(t_token token);
t_btree	*new_btree_void(void);

//error
void	exit_write_perror(char *s, t_data *data);
void	exit_write_error_cmd(t_data *data, char *s, char *s1);
void	write_double_error_one(char *cmd, char *s);
void	write_double_str_perror(char *s, char *s1);
void	write_error(char *s);
void	write_error_one(char *s);
void	write_perror(char *s);
void	write_triple_str_error(char *s, char *s1, char *s2);
void	free_all(t_data *data);
void	free_all_except_env(t_data *data);
void	exit_write_error(t_data *data, char *s, char *s1);
void	write_delim_str_error(char *s, char *s1);
void	close_redirections(t_data *data);
void	exit_write_double_perror(char *s, char *s1, t_data *data);
void	ft_putstr_fd_write_protected(char *str, int fd);

#endif

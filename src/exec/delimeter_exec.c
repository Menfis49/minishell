/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:02:45 by jholl             #+#    #+#             */
/*   Updated: 2022/01/30 15:37:37 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_left_delimeter(t_btree *ast, t_data *data)
{
	if (!ast)
		return ;
	if (ast->tok.type != 0 && ast->tok.type != TOK_LITTERAL
		&& ast->tok.type != TOK_PIPE)
	{
		check_left_delimeter(ast->left, data);
		if (ast->tok.type == TOK_DELIMETER)
			read_while_delimeter(ast->right->tok, data);
	}
}

void	delimeter_fork(t_data *data, t_btree *ast)
{
	int	pid;

	data->red.delimeter_entry++;
	pid = fork();
	if (pid < 0)
		exit_write_perror("fork function failed:", data);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		check_left_delimeter(ast->left, data);
		read_write_while_delimeter(ast->right->tok, data);
		free_all(data);
		exit(0);
	}
	else
		wait_delimiter_fork(data, pid);
}

int	first_delimeter(t_data *data, t_btree **ast)
{
	int	fd;

	data->red.first_input++;
	data->red.is_delimeter++;
	fd = treat_file((*ast)->tok, (*ast)->right->tok, data);
	if (fd < 0)
		return (fd);
	data->red.tmp_actual_count++;
	data->red.fd_input = fd;
	delimeter_fork(data, *ast);
	close(fd);
	return (1);
}

int	if_redirection_exec_delimiter(t_btree **ast, t_data *data)
{
	if (!data->red.first_input && (*ast)->tok.type == TOK_RED_INPUT)
		data->red.first_input++;
	else if (!data->red.first_input && (*ast)->tok.type == TOK_DELIMETER)
		return (first_delimeter(data, ast));
	else if (data->red.first_input && (*ast)->tok.type == TOK_DELIMETER)
	{
		if (!data->red.delimeter_entry)
			delimeter_fork(data, *ast);
	}
	return (1);
}

void	exec_delimiter(t_btree **ast, t_data *data)
{
	if (!(*ast))
		return ;
	if (is_redirection((*ast)->tok.type))
	{
		if (if_redirection_exec_delimiter(ast, data) < 0)
		{
			data->do_exec = 0;
			return ;
		}
	}
	if (is_pipe((*ast)->tok.type))
		reset_ret_data(data);
	if (!data->stop_delim)
		exec_delimiter(&(*ast)->left, data);
	return ;
}

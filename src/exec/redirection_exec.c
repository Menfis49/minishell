/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:10:42 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 02:54:56 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	treat_file(t_token tok, t_token right_tok, t_data *data)
{
	int	i;

	i = data->red.tmp_actual_count;
	if (tok.type == TOK_RED_INPUT)
		return (f_open_rdonly(right_tok.s[0]));
	if (tok.type == TOK_RED_OUTPUT)
		return (f_open_creat_rdwr_trunc(right_tok.s[0]));
	if (tok.type == TOK_RED_OUTPUT_APPENDS)
		return (f_open_creat_rdwr_append(right_tok.s[0]));
	if (tok.type == TOK_DELIMETER)
		return (f_open_creat_rdwr_trunc(data->red.tmp_files[i]));
	return (-1);
}

int	first_single_output(t_data *data, t_btree **ast)
{
	int	fd;

	data->red.first_output++;
	fd = treat_file((*ast)->tok, (*ast)->right->tok, data);
	if (fd < 0)
		return (fd);
	data->red.fd_output = fd;
	exec(&(*ast)->left, data);
	return (1);
}

int	first_single_input(t_data *data, t_btree **ast)
{
	int	fd;

	data->red.first_input++;
	fd = treat_file((*ast)->tok, (*ast)->right->tok, data);
	if (fd < 0)
		return (fd);
	data->red.fd_input = fd;
	exec(&(*ast)->left, data);
	return (1);
}

int	first_single_delim(t_data *data, t_btree **ast)
{
	int	fd;

	data->red.first_input++;
	fd = f_open_rdonly(data->red.tmp_files[data->red.tmp_cnt_exec]);
	if (fd < 0)
		return (fd);
	data->red.tmp_cnt_exec++;
	data->red.fd_input = fd;
	exec(&(*ast)->left, data);
	return (1);
}

int	if_redirection_exec(t_btree **ast, t_data *data)
{
	int	fd;

	if (!is_redirection((*ast)->tok.type))
		return (0);
	if (!data->red.first_input && (*ast)->tok.type == TOK_RED_INPUT)
		return (first_single_input(data, ast));
	else if (!data->red.first_input && (*ast)->tok.type == TOK_DELIMETER)
		return (first_single_delim(data, ast));
	else if (!data->red.first_output && ((*ast)->tok.type == TOK_RED_OUTPUT
			|| (*ast)->tok.type == TOK_RED_OUTPUT_APPENDS))
		return (first_single_output(data, ast));
	else if ((*ast)->tok.type != TOK_DELIMETER)
	{
		fd = treat_file((*ast)->tok, (*ast)->right->tok, data);
		if (fd < 0)
			return (fd);
		if (close(fd) < 0)
			exit_write_perror("Minishell: close function failed: ", data);
	}
	exec(&(*ast)->left, data);
	return (1);
}

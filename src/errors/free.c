/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:23:54 by jholl             #+#    #+#             */
/*   Updated: 2022/02/01 18:44:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dint(int **dint, t_data *data)
{
	int	i;

	if (!dint)
		return ;
	i = 0;
	while (i < data->pipe.nb_pipe)
	{
		free(data->pipe.dpipe_fd[i]);
		data->pipe.dpipe_fd[i] = NULL;
		i++;
	}
	free(dint);
}

void	free_all_extend(t_data *data)
{
	if (data->old_pwd)
		free(data->old_pwd);
	data->old_pwd = NULL;
	free_dint(data->pipe.dpipe_fd, data);
	data->pipe.dpipe_fd = NULL;
	close_redirections(data);
	if (data->line_read)
		free(data->line_read);
	data->line_read = NULL;
	rl_clear_history();
}

void	free_all(t_data *data)
{
	if (data->lexer)
		ft_lstdel_char(data->lexer, free_str);
	data->lexer = NULL;
	if (data->ast)
		del_btree(&data->ast, data);
	data->ast = NULL;
	if (data->pid)
		free(data->pid);
	data->pid = NULL;
	if (data->our_env)
		ft_lstdel_char(data->our_env, free_str);
	data->our_env = NULL;
	if (data->env)
		free(data->env);
	data->env = NULL;
	if (data->red.tmp_files)
		free_dstr(data->red.tmp_files);
	data->red.tmp_files = NULL;
	if (data->pwd)
		free(data->pwd);
	data->pwd = NULL;
	free_all_extend(data);
}

void	free_all_except_env(t_data *data)
{
	if (data->lexer)
		ft_lstdel_char(data->lexer, free_str);
	data->lexer = NULL;
	if (data->ast)
		del_btree(&data->ast, data);
	data->ast = NULL;
	if (data->pid)
		free(data->pid);
	data->pid = NULL;
	if (data->env)
		free(data->env);
	data->env = NULL;
	free_dint(data->pipe.dpipe_fd, data);
	if (data->red.tmp_files)
		free_dstr(data->red.tmp_files);
	data->red.tmp_files = NULL;
	data->pipe.dpipe_fd = NULL;
	if (data->line_read)
		free(data->line_read);
	data->line_read = NULL;
}

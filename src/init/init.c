/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:38:43 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 18:08:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pid(int cnt_pipe, t_data *data)
{
	int	*pid;
	int	i;
	int	size;

	size = cnt_pipe;
	pid = malloc(sizeof(int *) * (size + 1));
	if (!pid)
		exit_write_perror(MALLOC_ERROR, data);
	i = 0;
	pid[size] = -1;
	data->pid = pid;
}

void	dchar_env(t_data *data)
{
	t_list	*lst;
	char	**env;
	int		size;
	int		i;

	size = 0;
	lst = data->our_env;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		exit_write_perror(MALLOC_ERROR, data);
	lst = data->our_env;
	i = 0;
	while (lst)
	{
		env[i] = lst->content;
		lst = lst->next;
		i++;
	}
	env[i] = NULL;
	data->env = env;
}

void	reset_pipe_data(t_data *data)
{
	data->pipe.dpipe_fd = NULL;
	data->pipe.nb_pipe = 0;
	data->pipe.nb_pipe_created = 0;
	data->pipe.count = 0;
	data->pipe.read = 0;
	data->pipe.prev_read = 0;
}

void	reset_ret_data(t_data *data)
{
	data->red.fd_input = 0;
	data->red.fd_output = 1;
	data->red.first_input = 0;
	data->red.first_output = 0;
	data->red.is_delimeter = 0;
	data->red.delimeter_entry = 0;
}

void	init(t_data *data)
{
	data->do_exec = 1;
	data->nb_fork = 0;
	data->count_pid = 0;
	data->stop_delim = 0;
	data->red.tmp_actual_count = 0;
	data->red.tmp_cnt_exec = 0;
	data->red.tmp_files = NULL;
	reset_ret_data(data);
	reset_pipe_data(data);
	init_dpipe_fd(count_pipe(&data->lexer, data), data);
	init_pid(count_pipe(&data->lexer, data) + 1, data);
	dchar_env(data);
}

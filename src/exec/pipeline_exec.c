/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 00:58:34 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 18:58:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_pipeline_exec(t_btree **ast, t_data *data)
{
	if (data->pipe.count && data->pipe.count != data->pipe.nb_pipe)
	{
		data->pipe.prev_fd_pipe[0] = data->pipe.fd_pipe[0];
		data->pipe.prev_fd_pipe[1] = data->pipe.fd_pipe[1];
		data->pipe.prev_read = data->pipe.read;
	}
	if (pipe(data->pipe.fd_pipe) == -1)
		exit(g_exit_status);
	data->pipe.nb_pipe_created++;
	data->pipe.dpipe_fd[data->pipe.count][0] = data->pipe.fd_pipe[0];
	data->pipe.dpipe_fd[data->pipe.count][1] = data->pipe.fd_pipe[1];
	data->pipe.count++;
	data->pipe.read = 0;
	exec(&(*ast)->right, data);
	data->pipe.read = 1;
	close_redirections(data);
	reset_ret_data(data);
	if (data->pipe.count == data->pipe.nb_pipe)
		data->pipe.count++;
	exec(&(*ast)->left, data);
}

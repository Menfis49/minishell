/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:29:51 by jholl             #+#    #+#             */
/*   Updated: 2022/02/01 01:15:31 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_redirection(t_data *data)
{
	if (data->red.fd_input != 0)
	{
		dup2(data->red.fd_input, STDIN_FILENO);
		close(data->red.fd_input);
	}
	if (data->red.fd_output != 1)
	{
		dup2(data->red.fd_output, STDOUT_FILENO);
		close(data->red.fd_output);
	}
}

void	dup_two_pipes(t_data *data)
{
	if (data->pipe.read)
	{
		if (data->red.fd_input == 0)
			dup2(data->pipe.fd_pipe[0], STDIN_FILENO);
	}
	else
	{
		if (data->red.fd_output == 1)
			dup2(data->pipe.fd_pipe[1], STDOUT_FILENO);
	}
	if (data->pipe.prev_read)
	{
		if (data->red.fd_input == 0)
			dup2(data->pipe.prev_fd_pipe[0], STDIN_FILENO);
	}
	else
	{
		if (data->red.fd_output == 1)
			dup2(data->pipe.prev_fd_pipe[1], STDOUT_FILENO);
	}
}

void	dup_pipe(t_data *data)
{
	if (!data->pipe.count)
		return ;
	if (!((data->pipe.count > 1) && (data->pipe.count <= data->pipe.nb_pipe)))
	{
		if (data->pipe.read)
		{
			if (data->red.fd_input == 0)
				dup2(data->pipe.fd_pipe[0], STDIN_FILENO);
		}
		else
		{
			if (data->red.fd_output == 1)
				dup2(data->pipe.fd_pipe[1], STDOUT_FILENO);
		}
	}
	else
		dup_two_pipes(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_n_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:19:03 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 01:14:55 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_backslash(void)
{
	g_exit_status = 131;
	write(1, "Quit (core dumped)\n", 19);
}

void	ctrl_c(void)
{
	g_exit_status = 130;
	write(1, "\n", 1);
}

void	wait_pid(t_data *data)
{
	int	i;
	int	status;
	int	status_alrdy_treat;

	i = 0;
	status = 0;
	status_alrdy_treat = 0;
	while (i < data->nb_fork)
	{
		if (waitpid(data->pid[i], &status, 0) < 0)
			exit_write_perror("Minishell: waitpid problem: ", data);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && !status_alrdy_treat)
		{
			status_alrdy_treat = 1;
			if (WTERMSIG(status) == 2)
				ctrl_c();
			if (WTERMSIG(status) == 3)
				ctrl_backslash();
		}
		i++;
	}
}

void	wait_n_close(t_data *data)
{
	int	i;
	int	nb_pipe;

	nb_pipe = data->pipe.nb_pipe_created;
	if (nb_pipe == -1)
		nb_pipe++;
	i = 0;
	while (nb_pipe--)
	{
		close(data->pipe.dpipe_fd[i][0]);
		close(data->pipe.dpipe_fd[i][1]);
		i++;
	}
	wait_pid(data);
	signal(SIGINT, handle);
	while (data->red.tmp_actual_count--)
		unlink(data->red.tmp_files[data->red.tmp_actual_count]);
}

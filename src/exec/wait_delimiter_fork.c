/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_delimiter_fork.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:35:51 by jholl             #+#    #+#             */
/*   Updated: 2022/01/30 15:38:12 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_delimiter_fork(t_data *data, int pid)
{
	int	status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, &status, 0) < 0)
		exit_write_perror("waitpid function failed:", data);
	signal(SIGINT, SIG_DFL);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		data->do_exec = 0;
		if (WTERMSIG(status) == 2)
		{
			g_exit_status = 130;
			data->stop_delim = 1;
			write(1, "\n", 1);
		}
		if (WTERMSIG(status) == 3)
		{
			g_exit_status = 131;
			write(1, "Quit (core dumped)\n", 19);
		}
	}
}

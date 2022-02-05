/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   litteral_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:14:04 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 23:17:32 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipe.count > data->pipe.nb_pipe)
		data->pipe.count--;
	while (i < data->pipe.count)
	{
		if (data->pipe.dpipe_fd[i][0])
			close(data->pipe.dpipe_fd[i][0]);
		if (data->pipe.dpipe_fd[i][1])
			close(data->pipe.dpipe_fd[i][1]);
		i++;
	}	
}

void	cmd_exec(t_btree **ast, t_data *data)
{
	char	*path;

	path = access_command(data, (*ast)->tok.s[0]);
	dup_pipe(data);
	dup_redirection(data);
	close_pipe(data);
	if (execve(path, (*ast)->tok.s, data->env) < 0)
		exit_write_perror("execve function failed:", data);
	exit(g_exit_status);
}

int	if_builtin_exec(t_data *data, char **built)
{
	if (is_echo(built[0]))
		built_echo(built, data);
	else if (is_pwd(built[0]))
		built_pwd(data);
	else if (is_env(built[0]))
		built_env(built, data);
	else if (is_unset(built[0]))
		built_unset(data, built);
	else if (is_cd(built[0]))
		built_cd(built, data);
	else if (is_export(built[0]))
		built_export(data, built);
	else if (is_exit(built[0]))
		built_exit(data, built);
	else
		return (0);
	return (1);
}

int	if_builtin_fork_exec(t_data *data, char **built)
{
	if (!is_builtin(built[0]))
		return (0);
	dup_pipe(data);
	dup_redirection(data);
	close_pipe(data);
	if_builtin_exec(data, built);
	free_all(data);
	exit(g_exit_status);
	return (1);
}

void	if_litteral_exec(t_btree **ast, t_data *data)
{
	if (!((*ast)->tok.type == TOK_LITTERAL))
		return ;
	if (data->pipe.nb_pipe == 0)
	{
		if (if_builtin_exec(data, (*ast)->tok.s))
			data->pipe.nb_pipe--;
	}
	if (data->pipe.nb_pipe == -1)
		return ;
	data->count_pid++;
	data->nb_fork++;
	data->pid[data->count_pid - 1] = fork();
	if (data->pid[data->count_pid - 1] < 0)
		exit_write_perror("fork function failed:", data);
	if (!data->pid[data->count_pid - 1])
	{
		signal(SIGQUIT, SIG_DFL);
		if (if_builtin_fork_exec(data, (*ast)->tok.s))
			return ;
		else
			cmd_exec(ast, data);
	}
	else
		signal(SIGINT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_first.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 22:32:03 by jholl             #+#    #+#             */
/*   Updated: 2022/02/01 18:19:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_first(t_data *data)
{
	data->red.tmp_files = NULL;
	reset_ret_data(data);
	reset_pipe_data(data);
	data->pipe.dpipe_fd = NULL;
	data->count_pid = 0;
	data->pid = 0;
	data->lexer = NULL;
	data->ast = NULL;
	data->env = NULL;
	data->pwd = lf_var("PWD", data);
	data->old_pwd = lf_var("OLDPWD", data);
}

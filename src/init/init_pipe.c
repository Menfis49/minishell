/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 03:25:04 by jholl             #+#    #+#             */
/*   Updated: 2022/01/28 00:49:59 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(t_list **lexer, t_data *data)
{
	t_list	*tmp;
	int		cnt_pipe;

	tmp = *lexer;
	cnt_pipe = 0;
	while (tmp)
	{
		if (tmp->type == TOK_PIPE)
			cnt_pipe++;
		tmp = tmp->next;
	}
	data->pipe.nb_pipe = cnt_pipe;
	return (cnt_pipe);
}

void	init_dpipe_fd(int cnt_pipe, t_data *data)
{
	int	**dpipe_fd;
	int	i;

	if (!cnt_pipe)
		return ;
	dpipe_fd = malloc(sizeof(int *) * (cnt_pipe + 1));
	if (!dpipe_fd)
		exit_write_perror(MALLOC_ERROR, data);
	i = 0;
	while (i < cnt_pipe)
	{
		dpipe_fd[i] = malloc(sizeof(int) * 2);
		if (!dpipe_fd[i])
			exit_write_perror(MALLOC_ERROR, data);
		i++;
	}
	dpipe_fd[cnt_pipe] = NULL;
	data->pipe.dpipe_fd = dpipe_fd;
}

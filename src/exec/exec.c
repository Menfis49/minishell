/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:24:50 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 23:17:41 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_btree **ast, t_data *data)
{
	if (!(*ast))
		return ;
	if (is_redirection((*ast)->tok.type))
	{
		if (if_redirection_exec(ast, data) < 0)
			return ;
	}
	else if ((*ast)->tok.type == TOK_PIPE)
		if_pipeline_exec(ast, data);
	else
		if_litteral_exec(ast, data);
}

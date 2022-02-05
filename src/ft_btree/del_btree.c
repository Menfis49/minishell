/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_btree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 20:12:30 by jholl             #+#    #+#             */
/*   Updated: 2022/01/23 18:55:49 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_btree(t_btree **btree, t_data *data)
{
	t_btree	*del;

	del = *btree;
	if (!del)
		return ;
	del_btree(&del->right, data);
	del_btree(&del->left, data);
	if (del->tok.s)
		free(del->tok.s);
	free(del);
	del = NULL;
}

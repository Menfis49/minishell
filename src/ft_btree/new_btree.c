/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_btree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 20:23:38 by jholl             #+#    #+#             */
/*   Updated: 2022/01/23 17:39:00 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*new_btree_void(void)
{
	t_btree	*new_bt;

	new_bt = malloc(sizeof(t_btree));
	if (!new_bt)
		return (NULL);
	new_bt->tok.type = 0;
	new_bt->tok.s = NULL;
	new_bt->right = NULL;
	new_bt->left = NULL;
	return (new_bt);
}

t_btree	*new_btree(t_token token)
{
	t_btree	*new_bt;

	new_bt = malloc(sizeof(t_btree));
	if (!new_bt)
		return (NULL);
	new_bt->tok = token;
	new_bt->right = NULL;
	new_bt->left = NULL;
	return (new_bt);
}

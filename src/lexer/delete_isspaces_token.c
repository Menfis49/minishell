/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_isspaces_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:51:09 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 18:10:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_isspaces_token(t_list **lexer)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *lexer;
	while (lst)
	{
		tmp = lst->next;
		if (is_isspace(lst->type))
			ft_lst_delone(lexer, lst);
		lst = tmp;
	}
}

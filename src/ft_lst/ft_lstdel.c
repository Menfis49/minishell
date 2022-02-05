/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:12:07 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 01:15:43 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdel_char(t_list *lst, void (del)(char *))
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		del(lst->content);
		lst->content = NULL;
		free (lst);
		lst = temp;
	}
}

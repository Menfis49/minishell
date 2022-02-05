/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:38:50 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 01:15:57 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_to_del_content(t_list *to_del)
{
	if (to_del->content)
		free(to_del->content);
	free(to_del);
}

void	if_lst_is_to_del(t_list **list, t_list *lst, t_list *to_del)
{
	lst = (*list)->next;
	free_to_del_content(to_del);
	*list = lst;
}

void	ft_lst_delone(t_list **list, t_list *to_del)
{
	t_list	*lst;
	t_list	*tmp;

	if (!(*list) || !to_del)
		return ;
	lst = *list;
	if (lst == to_del)
		if_lst_is_to_del(list, lst, to_del);
	else
	{
		while (lst)
		{
			tmp = lst->next->next;
			if (lst->next == to_del)
			{
				free_to_del_content(to_del);
				lst->next = tmp;
				return ;
			}
			lst = lst->next;
		}
	}
}

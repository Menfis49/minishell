/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:16:07 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 01:16:09 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_list_find(t_list *list_start, void *data_ref, int (*cmp)())
{
	while (list_start)
	{
		if (!(*cmp)(list_start->content, data_ref))
			return (list_start);
		list_start = list_start->next;
	}
	return (0);
}

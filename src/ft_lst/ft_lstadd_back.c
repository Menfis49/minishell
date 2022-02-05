/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:38:02 by jholl             #+#    #+#             */
/*   Updated: 2022/01/23 14:25:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	temp = *alst;
	if (*alst)
	{
		while ((*alst)->next)
			*alst = (*alst)->next;
		(*alst)->next = new;
		*alst = temp;
	}
	else
		*alst = new;
}

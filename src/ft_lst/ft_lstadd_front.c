/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:18:12 by jholl             #+#    #+#             */
/*   Updated: 2022/01/10 23:18:24 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list		*temp;

	if (alst == NULL || new == NULL)
		return ;
	temp = *alst;
	*alst = new;
	(*alst)->next = temp;
}

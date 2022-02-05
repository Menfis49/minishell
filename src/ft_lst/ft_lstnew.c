/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:35:49 by jholl             #+#    #+#             */
/*   Updated: 2022/01/23 14:25:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *s)
{
	t_list	*new_ptr;

	new_ptr = (t_list *)malloc(sizeof(t_list) * 1);
	if (!new_ptr)
		return (NULL);
	new_ptr->content = s;
	new_ptr->next = NULL;
	return (new_ptr);
}

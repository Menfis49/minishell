/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_special_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vazra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:11:51 by vazra             #+#    #+#             */
/*   Updated: 2022/02/03 13:44:54 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_special_case(t_list *lst)
{
	if (!(lst))
		return (0);
	if (lst->type == 1 || lst->type == 99)
		return (1);
	return (0);
}

t_list	*while_special_type(t_data *data, t_list *lst, int *skip)
{
	if (lst->next)
	{
		if (lst->next->type == 1 || lst->next->type == 99)
		{
			ft_lst_delone(&data->lexer, lst);
			regroup_token(data->lexer, data);
			lst = data->lexer;
			*skip = 1;
		}
		else if (lst->next->type == 2)
		{
			if (!delete_special_case(lst->next->next))
				lst->type = 98;
			else
			{
				ft_lst_delone(&data->lexer, lst);
				regroup_token(data->lexer, data);
				lst = data->lexer;
				*skip = 1;
			}
		}
	}
	return (lst);
}

void	pars_special_case(t_data *data)
{
	t_list	*lst;
	int		skip;

	lst = data->lexer;
	while (lst)
	{
		skip = 0;
		while (lst->next && lst->type == 99)
		{
			lst = (while_special_type(data, lst, &skip));
			if (!lst)
				break ;
			if (lst && !skip)
				lst = lst->next;
		}
		if (lst && !skip)
			lst = lst->next;
	}
}

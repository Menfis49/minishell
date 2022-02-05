/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_order_pipe_lexer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:36:00 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:36:03 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_pipe_after(t_list **lexer)
{
	t_list	*lst;

	lst = (*lexer)->next;
	while (lst)
	{
		if (lst->type == TOK_PIPE)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	reverse_place(t_list **lexer, t_list **new)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *lexer;
	while (lst)
	{
		if (lst->type == TOK_PIPE)
		{
			if (check_if_pipe_after(&lst))
				;
			else
			{
				ft_lstadd_back(new, lst->next);
				lst->next = NULL;
				ft_lstadd_back(new, lst);
				tmp->next = NULL;
				break ;
			}
		}
		tmp = lst;
		lst = lst->next;
	}
}

void	reverse_order_pipe_lexer(t_list **lexer, t_data *data)
{
	t_list	*new;
	int		nb_pipe;

	new = NULL;
	nb_pipe = data->pipe.nb_pipe;
	if (!nb_pipe)
		return ;
	while (nb_pipe--)
		reverse_place(lexer, &new);
	ft_lstadd_back(&new, (*lexer));
	data->lexer = new;
}

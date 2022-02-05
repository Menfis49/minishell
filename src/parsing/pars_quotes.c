/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 19:58:36 by jholl             #+#    #+#             */
/*   Updated: 2022/02/03 14:31:42 by vazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	treat_quotes(t_list **lexer, t_list **save_lexer, int dq, t_data *data)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *lexer;
	while (lst)
	{
		if (dq && lst->type == TOK_VAR)
			treat_var(&lst, save_lexer, data);
		if ((lst->type == 6 && !dq) || (lst->type == 5 && dq))
			return ;
		if (lst->type == 99 || lst->type == 98)
		{
			tmp = lst->next;
			ft_lst_delone(save_lexer, lst);
			lst = tmp;
		}
		else
		{
			lst->type = TOK_LITTERAL;
			lst = lst->next;
		}
	}
}

int	lf_end_quote(t_list *lexer, int dq)
{
	while (lexer)
	{
		if ((lexer->type == TOK_SINGLE_QUOTE && !dq) || (lexer->type
				== TOK_DOUBLE_QUOTE && dq))
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

int	lexer_next_is_quote(t_data *data, t_list **lexer, int dq)
{
	if ((*lexer)->next)
	{
		if (((*lexer)->next->type == TOK_SINGLE_QUOTE && !dq)
			|| ((*lexer)->next->type == TOK_DOUBLE_QUOTE && dq))
		{
			ft_lst_delone(&data->lexer, (*lexer)->next);
			(*lexer)->content[0] = '\0';
			(*lexer)->type = TOK_LITTERAL;
			return (1);
		}
	}
	return (0);
}

void	locate_next_quote_delete(t_data *data, int dq, t_list **lexer)
{
	t_list	*lst;

	lst = *lexer;
	while (lst)
	{
		if ((lst->type == TOK_SINGLE_QUOTE && !dq) || (lst->type
				== TOK_DOUBLE_QUOTE && dq))
		{
			ft_lst_delone(&data->lexer, lst);
			return ;
		}
		lst = lst->next;
	}
}

void	pars_quotes(t_list **lexer, t_list **save_lexer, t_data *data, int dq)
{
	if ((*lexer)->type == TOK_DOUBLE_QUOTE)
		dq = 1;
	if (!lf_end_quote((*lexer)->next, dq))
	{
		(*lexer)->type = TOK_LITTERAL;
		regroup_token((*save_lexer), data);
		return ;
	}
	else
	{
		if (lexer_next_is_quote(data, lexer, dq))
			return ;
		treat_quotes(&(*lexer)->next, save_lexer, dq, data);
		if (lexer_next_is_quote(data, lexer, dq))
			return ;
		locate_next_quote_delete(data, dq, &(*lexer)->next);
		ft_lst_delone(save_lexer, *lexer);
	}
	regroup_token((*save_lexer), data);
}

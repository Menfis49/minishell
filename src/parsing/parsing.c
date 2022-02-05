/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:21:16 by jholl             #+#    #+#             */
/*   Updated: 2022/02/03 12:08:26 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_operators(t_data *data)
{
	t_list	*lst;

	pars_special_case(data);
	lst = data->lexer;
	while (lst)
	{
		if (!pars_operator(lst))
			return (0);
		if (lst)
			lst = lst->next;
	}
	return (1);
}

void	parsing_tok_var(t_list *lst, t_data *data, t_list **lexer)
{
	treat_var(&lst, lexer, data);
	regroup_token(data->lexer, data);
}

int	parsing(t_data *data, t_list **lexer)
{
	t_list	*lst;
	int		double_quote;
	int		skip;

	lst = *lexer;
	while (lst)
	{
		skip = 0;
		if (lst->type == TOK_DOUBLE_QUOTE || lst->type == TOK_SINGLE_QUOTE)
		{
			double_quote = 0;
			pars_quotes(&lst, &data->lexer, data, double_quote);
			lst = data->lexer;
			skip = 1;
		}
		else if (lst->type == TOK_VAR)
		{
			parsing_tok_var(lst, data, lexer);
			lst = data->lexer;
			skip = 1;
		}
		if (lst && !skip)
			lst = lst->next;
	}
	return (pars_operators(data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:55:06 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:38:33 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_ast(t_btree **ast, t_token token, t_data *data)
{
	t_btree	*new_node;

	if (*ast && !is_operator(token.type))
	{
		redirection_exception(ast, token, data);
		add_to_ast(&(*ast)->right, token, data);
	}
	else if (*ast && is_operator(token.type))
	{
		new_node = new_btree(token);
		if (!new_node)
			exit_write_perror(MALLOC_ERROR, data);
		new_node->left = *ast;
		*ast = new_node;
	}
	else
	{
		*ast = new_btree(token);
		if (!(*ast))
			exit_write_perror(MALLOC_ERROR, data);
	}
}

static void	init_vars(int *lexer_position, int *count_args, t_btree **ast)
{
	*ast = NULL;
	*count_args = 0;
	*lexer_position = 0;
}

void	create_ast(t_btree **ast, t_list **lexer, t_data *data)
{
	int		count_args;
	int		lexer_position;
	t_list	*lst;
	t_list	*tmp;

	init_vars(&lexer_position, &count_args, ast);
	lst = *lexer;
	while (lst)
	{
		tmp = lst->next;
		if (!is_operator(lst->type))
		{
			count_args++;
			if (!(lst->next))
				add_litteral(lexer_position, count_args, lexer, data);
		}
		else
		{
			add_litteral(lexer_position, count_args, lexer, data);
			count_args++;
			lexer_position = count_args;
			add_operator(lst, ast, data);
		}
		lst = tmp;
	}
}

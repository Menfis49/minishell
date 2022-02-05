/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:30:44 by user42            #+#    #+#             */
/*   Updated: 2022/01/27 21:14:21 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_operator(t_list *lexer, t_btree **ast, t_data *data)
{
	char	**ope;
	t_token	new_tok;

	ope = malloc(sizeof(char *) * 2);
	if (!ope)
		exit_write_perror(MALLOC_ERROR, data);
	ope[0] = lexer->content;
	ope[1] = NULL;
	new_tok.type = lexer->type;
	new_tok.s = ope;
	add_to_ast(ast, new_tok, data);
}

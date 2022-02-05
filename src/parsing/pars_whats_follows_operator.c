/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_whats_follows_operator.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 02:59:59 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 22:19:21 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_syntax_operator_error(t_list *lexer)
{
	if ((*lexer).type == TOK_DELIMETER)
		write_error("minishell: syntax error near unexpected token `<<'");
	if ((*lexer).type == TOK_RED_INPUT)
		write_error("minishell: syntax error near unexpected token `<'");
	if ((*lexer).type == TOK_RED_OUTPUT)
		write_error("minishell: syntax error near unexpected token `>'");
	if ((*lexer).type == TOK_RED_OUTPUT_APPENDS)
		write_error("minishell: syntax error near unexpected token `>>'");
	if ((*lexer).type == TOK_PIPE)
		write_error("minishell: syntax error near unexpected token `|'");
}

int	pars_what_follows_operator(t_list *lexer, int *pipe)
{
	if (!lexer->next)
		write_error("minishell: syntax error near unexpected token `newline'");
	if (!lexer->next)
		return (0);
	if (lexer->next->type == TOK_ISSPACE)
		return (pars_what_follows_operator(lexer->next, pipe));
	if (lexer->next->type == TOK_LITTERAL || lexer->next->type == 99)
		return (1);
	if (is_operator(lexer->next->type))
	{
		lexer = lexer->next;
		if (*pipe == 1)
		{
			if ((*lexer).type == TOK_PIPE)
				write_error(
					"minishell: syntax error near unexpected token `|'");
			if (is_redirection((*lexer).type))
				*pipe = 0;
			if (is_redirection((*lexer).type))
				return (pars_what_follows_operator(lexer, pipe));
		}
		else
			parsing_syntax_operator_error(lexer);
	}
	return (0);
}

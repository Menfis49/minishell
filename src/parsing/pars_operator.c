/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:21:48 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 03:06:10 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_red_input(t_list *lexer)
{
	if (ft_strlen(lexer->content) == 2)
		lexer->type = TOK_DELIMETER;
	if (ft_strlen(lexer->content) > 2)
	{
		write_error("minishell: syntax error near unexpected token `>'");
		return (0);
	}
	return (1);
}

int	pars_red_output(t_list *lexer)
{
	if (ft_strlen(lexer->content) == 2)
		lexer->type = TOK_RED_OUTPUT_APPENDS;
	if (ft_strlen(lexer->content) > 2)
	{
		write_error("minishell: syntax error near unexpected token `<'");
		return (0);
	}
	return (1);
}

int	pars_pipe(t_list *lexer)
{
	if (ft_strlen(lexer->content) > 1)
	{
		write_error("minishell: syntax error near unexpected token `|'");
		return (0);
	}
	return (1);
}

int	pars_operator(t_list *lexer)
{
	int	pipe;

	pipe = 0;
	if (is_operator(lexer->type))
	{
		if (lexer->type == TOK_RED_INPUT)
			if (!pars_red_input(lexer))
				return (0);
		if (lexer->type == TOK_RED_OUTPUT)
			if (!pars_red_output(lexer))
				return (0);
		if (lexer->type == TOK_PIPE)
			if (!pars_pipe(lexer))
				return (0);
		if (lexer->type == TOK_PIPE)
		{
			pipe = 1;
			if (!pars_what_follows_operator(lexer, &pipe))
				return (0);
		}
		else
			if (!pars_what_follows_operator(lexer, &pipe))
				return (0);
	}
	return (1);
}

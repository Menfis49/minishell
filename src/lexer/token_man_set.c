/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_man_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:35:37 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:35:41 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_man_set_type(int i)
{
	if (i == 0)
		return (TOK_PIPE);
	if (i == 1)
		return (TOK_VAR);
	if (i == 2)
		return (TOK_DOUBLE_QUOTE);
	if (i == 3)
		return (TOK_SINGLE_QUOTE);
	if (i == 4)
		return (TOK_RED_INPUT);
	if (i == 5)
		return (TOK_RED_OUTPUT);
	if (i == 6)
		return (TOK_ISSPACE);
	if (i == 7)
		return (TOK_ISSPACE);
	if (i == 8)
		return (TOK_ISSPACE);
	if (i == 9)
		return (TOK_ISSPACE);
	if (i == 10)
		return (TOK_ISSPACE);
	if (i == 11)
		return (TOK_ISSPACE);
	return (0);
}

int	token_man_set_char(int i)
{
	if (i == 0)
		return ('|');
	if (i == 1)
		return ('$');
	if (i == 2)
		return ('"');
	if (i == 3)
		return ('\'');
	if (i == 4)
		return ('<');
	if (i == 5)
		return ('>');
	if (i == 6)
		return (' ');
	if (i == 7)
		return ('\v');
	if (i == 8)
		return ('\t');
	if (i == 9)
		return ('\r');
	if (i == 10)
		return ('\f');
	if (i == 11)
		return ('\n');
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:19:13 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 01:19:15 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iq(enum e_token_type type)
{
	if (type == TOK_SINGLE_QUOTE || type == TOK_DOUBLE_QUOTE)
		return (1);
	return (0);
}

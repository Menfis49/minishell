/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regroup_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:09:00 by jholl             #+#    #+#             */
/*   Updated: 2022/02/03 13:00:16 by vazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	regroup(t_list *lexer, t_list *temp, t_data *data)
{
	char	*s;

	if (lexer->next->next)
		temp = lexer->next->next;
	else
		temp = NULL;
	if (!(lexer->content && lexer->next->content))
		;
	else
	{
		s = ft_strjoin(lexer->content, lexer->next->content);
		if (lexer->content)
			free(lexer->content);
		if (lexer->next->content)
			free(lexer->next->content);
		if (!s)
			exit_write_perror(MALLOC_ERROR, data);
		lexer->content = s;
	}
	free(lexer->next);
	lexer->next = temp;
}

void	regroup_token(t_list *lexer, t_data *data)
{
	t_list	*temp;

	temp = NULL;
	while (lexer)
	{
		if (lexer->next && lexer->type == lexer->next->type && !iq(lexer->type))
			regroup(lexer, temp, data);
		else
			lexer = lexer->next;
	}
}

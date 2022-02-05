/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:08:49 by jholl             #+#    #+#             */
/*   Updated: 2022/01/27 01:52:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_new_s(char *new_s, char c, t_data *data)
{
	new_s = malloc(sizeof(char) * 2);
	if (!new_s)
		exit_write_perror(MALLOC_ERROR, data);
	new_s[0] = c;
	new_s[1] = '\0';
	return (new_s);
}

void	add_to_existing_lexer(t_list **lex, char *s, int *tok_val, t_data *data)
{
	t_list	*new_node;

	new_node = malloc(sizeof (t_list) * 1);
	if (!new_node)
	{
		free(s);
		exit_write_perror(MALLOC_ERROR, data);
	}
	new_node->content = s;
	new_node->type = *tok_val;
	new_node->next = NULL;
	ft_lstadd_back(lex, new_node);
}	

void	add_to_lexer(t_list **lexer, int *tok_val, char c, t_data *data)
{
	char	*new_s;

	new_s = NULL;
	new_s = create_new_s(new_s, c, data);
	if (!*lexer)
	{
		*lexer = ft_lstnew(new_s);
		if (!lexer)
		{
			free(new_s);
			exit_write_perror(MALLOC_ERROR, data);
		}
		(*lexer)->type = *tok_val;
	}
	else
		add_to_existing_lexer(lexer, new_s, tok_val, data);
}

void	identify_token(char c, int *tok_val)
{
	int			i;
	t_token_man	tok_man[13];

	i = 0;
	*tok_val = 1;
	while (i < 13)
	{
		tok_man[i].type = token_man_set_type(i);
		tok_man[i].char_token = token_man_set_char(i);
		i++;
	}
	i = 0;
	while (tok_man[i].type)
	{
		if (c == tok_man[i].char_token)
		{
			*tok_val = tok_man[i].type;
			return ;
		}
		i++;
	}
}

void	lexing(char *s, t_list **lexer, t_data *data)
{
	int	i;
	int	tok_val;

	*lexer = NULL;
	i = 0;
	while (s[i])
	{
		identify_token(s[i], &tok_val);
		add_to_lexer(lexer, &tok_val, s[i], data);
		i++;
	}
	if (s[0])
		regroup_token(*lexer, data);
}

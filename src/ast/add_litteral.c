/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_litteral.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:28:30 by user42            #+#    #+#             */
/*   Updated: 2022/02/03 11:46:57 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cmd(char **cmd, t_list *lst, int nb_args)
{
	int	i;

	i = 0;
	while (nb_args)
	{
		cmd[i] = lst->content;
		lst = lst->next;
		i++;
		nb_args--;
	}
}

void	add_litteral(int pos, int count, t_list **lexer, t_data *data)
{
	char	**cmd;
	int		nb_args;
	t_token	new_tok;
	t_list	*lst;

	lst = *lexer;
	nb_args = count - pos;
	if (nb_args)
	{
		while (pos)
		{
			lst = lst->next;
			pos--;
		}
		cmd = malloc(sizeof(char *) * (nb_args + 1));
		if (!cmd)
			exit_write_perror(MALLOC_ERROR, data);
		cmd[nb_args] = NULL;
		set_cmd(cmd, lst, nb_args);
		new_tok.type = TOK_LITTERAL;
		if ((lst->type == 98 || lst->type == 99) && nb_args == 1)
			new_tok.type = 99;
		new_tok.s = cmd;
		add_to_ast(&data->ast, new_tok, data);
	}
}

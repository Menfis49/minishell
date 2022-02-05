/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:29:45 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 22:23:05 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_exit_status(char *s, t_data *data)
{
	char	*new_s;
	char	*new_s1;
	int		size;

	new_s1 = NULL;
	new_s = ft_itoa(g_exit_status, data);
	if (!new_s)
		exit_write_perror(MALLOC_ERROR, data);
	size = ft_strlen(new_s) + ft_strlen(s) - 1;
	new_s1 = malloc(sizeof(char) * (size + 1));
	if (!new_s1)
	{
		free(new_s);
		exit_write_perror(MALLOC_ERROR, data);
	}
	new_s1[size] = '\0';
	ft_strlcpy(new_s1, new_s, ft_strlen(new_s) + 1);
	ft_strlcat(new_s1, s + 1, size);
	free(new_s);
	return (new_s1);
}

void	treat_var(t_list **lexer, t_list **save_lexer, t_data *data)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *lexer;
	tmp = lst->next;
	if (tmp)
	{
		if (tmp->type == TOK_LITTERAL)
		{
			free_str(lst->content);
			lst->content = NULL;
			if (tmp->content[0] == '?')
				lst->content = var_exit_status(tmp->content, data);
			else
				lst->content = lf_var(tmp->content, data);
			lst->type = TOK_LITTERAL;
			ft_lst_delone(save_lexer, tmp);
			if (!lst->content)
				lst->type = 99;
		}
		else
			lst->type = TOK_LITTERAL;
		return ;
	}
	lst->type = TOK_LITTERAL;
}

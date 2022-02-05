/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_exception.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:56:31 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 18:43:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**concatanate_prev_n_ds(char **second, char **first, t_data *data)
{
	char	**new_ds;

	new_ds = malloc(sizeof(char *) * (ft_nb_str(second) - 1 \
		+ ft_nb_str(first) + 1));
	if (!new_ds)
	{
		if (second)
			free(second);
		second = NULL;
		exit_write_perror(MALLOC_ERROR, data);
	}
	set_new_ds(new_ds, second, first);
	free(first);
	return (new_ds);
}

char	**create_new_ds_without_first(char **old_ds, t_data *data)
{
	char	**new_ds;
	int		i;
	int		size;

	size = ft_nb_str(old_ds);
	new_ds = NULL;
	new_ds = malloc(sizeof(char *) * (size));
	if (!new_ds)
	{
		if (old_ds)
			free(old_ds);
		old_ds = NULL;
		exit_write_perror(MALLOC_ERROR, data);
	}
	i = 1;
	while (old_ds[i])
	{
		new_ds[i - 1] = old_ds[i];
		old_ds[i] = NULL;
		i++;
	}
	new_ds[size - 1] = NULL;
	return (new_ds);
}

void	create_new_branch(t_btree **ast, t_token token, t_data *data)
{
	char	**new_ds;

	new_ds = NULL;
	*ast = new_btree_void();
	if (!(*ast))
	{
		if (token.s)
			free_dstr(token.s);
		token.s = NULL;
		exit_write_perror(MALLOC_ERROR, data);
	}
	(*ast)->tok.s = NULL;
	new_ds = create_new_ds_without_first(token.s, data);
	(*ast)->tok.s = new_ds;
	(*ast)->tok.type = token.type;
}

void	add_to_prev_litteral_content(t_btree **ast, t_token token, t_data *data)
{
	char	**new_ds;

	new_ds = NULL;
	if (*ast)
	{
		if (is_redirection((*ast)->tok.type))
		{
			add_to_prev_litteral_content(&(*ast)->left, token, data);
			return ;
		}
		if (is_pipe((*ast)->tok.type))
		{
			add_to_prev_litteral_content(&(*ast)->right, token, data);
			return ;
		}
	}
	if (!(*ast))
		create_new_branch(ast, token, data);
	else
	{
		new_ds = concatanate_prev_n_ds(token.s, (*ast)->tok.s, data);
		(*ast)->tok.s = new_ds;
		(*ast)->tok.type = token.type;
	}
}

void	redirection_exception(t_btree **ast, t_token token, t_data *data)
{
	if (*ast)
		if (is_redirection((*ast)->tok.type))
			if (ft_nb_str(token.s) > 1)
				add_to_prev_litteral_content(&(*ast)->left, token, data);
}

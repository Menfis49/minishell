/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_delimiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:53:08 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 18:18:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_digit(int i)
{
	int	count;

	count = 0;
	while (i >= 10)
	{
		i /= 10;
		count++;
	}
	count++;
	return (count);
}

void	count_delim_per_pipe(t_data *data)
{
	t_list	*lst;
	int		pipe;

	pipe = 1;
	data->red.tmp_files = NULL;
	data->red.tmp_count = 0;
	lst = data->lexer;
	while (lst)
	{
		if (lst->type == TOK_PIPE)
			pipe = 1;
		if (lst->type == TOK_DELIMETER && pipe)
		{
			data->red.tmp_count++;
			pipe = 0;
		}
		lst = lst->next;
	}
}

void	free_and_exit(char *new_s, t_data *data)
{
	free(new_s);
	exit_write_perror(MALLOC_ERROR, data);
}

void	malloc_new_ds_and_s(t_data *data, char **new_ds)
{
	int		i;
	int		size;
	char	*new_s;
	char	*new_s1;

	i = 0;
	while (i < data->red.tmp_count)
	{
		size = ft_strlen(TMP_FILES) + count_digit(i);
		new_s = malloc(sizeof(char) * (size + 1));
		if (!new_s)
			exit_write_perror(MALLOC_ERROR, data);
		new_s[size] = '\0';
		ft_strlcpy(new_s, TMP_FILES, ft_strlen(TMP_FILES) + 1);
		new_s1 = ft_itoa(i, data);
		if (!new_s1)
			free_and_exit(new_s, data);
		ft_strlcat(new_s, new_s1, ft_strlen(TMP_FILES)
			+ count_digit(i) + 1);
		free(new_s1);
		new_ds[i] = new_s;
		i++;
	}
}

void	init_delimiter(t_data *data)
{
	char	**new_ds;
	int		i;

	new_ds = NULL;
	count_delim_per_pipe(data);
	if (!data->red.tmp_count)
		return ;
	else
	{
		new_ds = malloc(sizeof(char *) * (data->red.tmp_count + 1));
		if (!new_ds)
			exit_write_perror(MALLOC_ERROR, data);
		new_ds[data->red.tmp_count] = NULL;
		data->red.tmp_files = new_ds;
		i = 0;
		while (i < data->red.tmp_count)
		{
			data->red.tmp_files[i] = NULL;
			i++;
		}
		malloc_new_ds_and_s(data, new_ds);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:37:04 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:37:39 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_to_add(char *to_add, char *name, char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(name))
	{
		to_add[i] = name[i];
		i++;
	}
	to_add[i] = '=';
	i++;
	if (value)
	{
		while (j < ft_strlen(value))
		{
			to_add[i] = value[j];
			i++;
			j++;
		}
	}
	to_add[i] = '\0';
}

void	add_var(t_data *data, char *name, char *value)
{
	t_list	*new;
	char	*to_add;

	if (!value)
		to_add = malloc(sizeof(char) * (ft_strlen(name) + 2));
	else
		to_add = malloc(sizeof(char) * (ft_strlen(name)
					+ ft_strlen(value) + 2));
	if (!to_add)
		exit_write_perror(MALLOC_ERROR, data);
	create_to_add(to_add, name, value);
	new = ft_lstnew(to_add);
	if (!data->our_env)
		data->our_env = new;
	else
		ft_lstadd_back(&(data->our_env), new);
}

void	set_env(t_data *data, char *name, char *value)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(name);
	tmp = ft_list_find(data->our_env, name, &check_if_var_exist);
	if (!tmp)
		add_var(data, name, value);
	else if (tmp && len)
		modify_existed_var(tmp, value, data);
}

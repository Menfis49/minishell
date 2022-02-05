/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_existed_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:36:37 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:36:39 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_creation(char *value, char *new_var_env, int j)
{
	int	i;

	i = 0;
	if (value)
	{
		while (i < ft_strlen(value))
		{
			new_var_env[j] = value[i];
			j++;
			i++;
		}
	}
	new_var_env[j] = '\0';
}

char	*create_new_var_env(t_list *tmp, t_list *lst, char *value, t_data *data)
{
	char	*new_var_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (lst->content[i] && lst->content[i] != '=')
		i++;
	if (!value)
		new_var_env = malloc(sizeof(char) * (i + 2));
	else
		new_var_env = malloc(sizeof(char) * (i + ft_strlen(value) + 2));
	if (!new_var_env)
		exit_write_perror(MALLOC_ERROR, data);
	while (j < i)
	{
		new_var_env[j] = tmp->content[j];
		j++;
	}
	new_var_env[j] = '=';
	j++;
	finish_creation(value, new_var_env, j);
	return (new_var_env);
}

void	modify_existed_var(t_list *tmp, char *value, t_data *data)
{
	t_list	*lst;
	char	*new_var_env;
	int		i;
	int		j;

	lst = tmp;
	i = 0;
	j = 0;
	new_var_env = create_new_var_env(tmp, lst, value, data);
	free(tmp->content);
	tmp->content = new_var_env;
}

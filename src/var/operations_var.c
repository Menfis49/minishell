/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 20:05:38 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 21:25:59 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_var_exist(char *s1, char *s2)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	if (!s2[i])
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		if (s1[i + 1] == '=' && s2[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}

char	*malloc_value(t_list *lst, char *var, char *val, t_data *data)
{
	int	i;
	int	j;
	int	len_var;

	len_var = ft_strlen(var);
	if (lst->content[len_var] == '=')
	{
		len_var++;
		i = len_var;
		val = malloc(sizeof(*val) * (ft_strlen(lst->content) - (len_var) + 1));
		if (!val)
			exit_write_perror(MALLOC_ERROR, data);
		j = 0;
		while (lst->content[i])
		{
			val[j] = lst->content[i];
			i++;
			j++;
		}
		val[j] = '\0';
		return (val);
	}
	return (NULL);
}

char	*lf_var(char *var, t_data *data)
{
	char	*value;
	t_list	*lst;
	int		i;
	int		len_var;

	lst = data->our_env;
	i = 0;
	len_var = ft_strlen(var);
	value = NULL;
	while (lst)
	{
		if (ft_strncmp(lst->content, var, len_var) == 0)
		{
			value = malloc_value(lst, var, value, data);
			if (value)
				return (value);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	*duplicate_value_env(t_data *data, char *var_name)
{
	char	*value_var;
	char	*duplicate_value;

	if (data->our_env)
	{
		value_var = lf_var(var_name, data);
		if (!value_var)
			return (0);
		else
		{
			duplicate_value = ft_strdup(value_var);
			if (!duplicate_value)
				exit_write_perror(MALLOC_ERROR, data);
		}
		return (duplicate_value);
	}
	return (0);
}

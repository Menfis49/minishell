/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:12:35 by jholl             #+#    #+#             */
/*   Updated: 2022/02/01 16:21:44 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_unset(char *built)
{
	if (!ft_is_alpha(built[0]))
	{
		if (built[0] == '$' && built[1] != '\0')
			return (1);
		return (0);
	}
	return (1);
}

int	is_unset(char *s)
{
	if (ft_strlen(s) == 5)
	{
		if (s[0] == 'u' && s[1] == 'n' && s[2] == 's' && s[3] == 'e'
			&& s[4] == 't')
			return (1);
	}
	return (0);
}

int	is_in_env(char *content, char *built)
{
	int	i;

	i = ft_strlen(built);
	if (!ft_strncmp(content, built, i))
	{
		if (content[i] == '=')
			return (1);
	}
	return (0);
}

void	check_for_delete(t_data *data, char *built)
{
	t_list	*lst;

	lst = data->our_env;
	while (lst)
	{
		if (is_in_env(lst->content, built))
		{
			ft_lst_delone(&data->our_env, lst);
			return ;
		}
		lst = lst->next;
	}
}

void	built_unset(t_data *data, char **built)
{
	int	i;

	i = 1;
	g_exit_status = 0;
	if (!built[i])
		return ;
	while (built[i])
	{
		if (!parsing_unset(built[i]))
		{
			write_double_error_one("unset: ", built[i]);
			g_exit_status = 1;
		}
		else
			check_for_delete(data, built[i]);
		i++;
		if (built[i])
			if (built[i][0] == '\0')
				break ;
	}
}

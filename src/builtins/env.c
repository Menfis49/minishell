/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:10:42 by jholl             #+#    #+#             */
/*   Updated: 2022/02/03 10:55:36 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_env(char **built)
{
	if (built[1])
	{
		write_error("Minishell: Env: 42 version not allowed options or args.");
		return (0);
	}
	return (1);
}

int	is_env(char *s)
{
	if (ft_strlen(s) == 3)
	{
		if (s[0] == 'e' && s[1] == 'n' && s[2] == 'v')
			return (1);
	}
	return (0);
}

void	env_only_data(t_data *data)
{
	t_list	*lst;

	lst = data->our_env;
	while (lst)
	{
		ft_putstr_fd("declare -x ", data->red.fd_output);
		ft_putstr_fd(lst->content, data->red.fd_output);
		ft_putstr_fd("\n", data->red.fd_output);
		lst = lst->next;
	}
	g_exit_status = 0;
}

void	built_env(char **built, t_data *data)
{
	t_list	*lst;
	int		i;

	if (!parsing_env(built))
		return ;
	i = 0;
	lst = data->our_env;
	while (lst)
	{
		if (!i)
			ft_putstr_fd_write_protected(lst->content, data->red.fd_output);
		else
			ft_putstr_fd(lst->content, data->red.fd_output);
		ft_putstr_fd("\n", data->red.fd_output);
		lst = lst->next;
		i++;
	}
	g_exit_status = 0;
}

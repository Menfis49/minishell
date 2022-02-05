/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:07:37 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 23:53:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pwd(char *s)
{
	if (ft_strlen(s) == 3)
	{
		if (s[0] == 'p' && s[1] == 'w' && s[2] == 'd')
			return (1);
	}
	return (0);
}

void	built_pwd(t_data *data)
{
	char	pwd[1024];

	if (!getcwd(pwd, 1024))
	{
		if (errno == 2)
		{
			ft_putstr_fd(data->pwd, data->red.fd_output);
			ft_putstr_fd("\n", data->red.fd_output);
		}
		else
			write_perror("Minishell: pwd: ");
		return ;
	}
	ft_putstr_fd(pwd, data->red.fd_output);
	ft_putstr_fd("\n", data->red.fd_output);
	g_exit_status = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:09:06 by jholl             #+#    #+#             */
/*   Updated: 2022/02/03 10:41:59 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flags(char **built, int i)
{
	int	j;
	int	arg_n;

	arg_n = 0;
	while (built[i])
	{
		if (built[i][0] == '-' && built[i][1] == 'n')
		{
			j = 2;
			if (built[i][j] == '\0')
				;
			else
			{
				while (built[i][j] && built[i][j] == 'n')
					j++;
				if (built[i][j] != '\0')
					break ;
			}
			arg_n++;
		}
		else
			break ;
		i++;
	}
	return (arg_n);
}

int	parsing_echo(char **built)
{
	int	i;
	int	arg_n;

	i = 1;
	arg_n = 0;
	if (!built[i])
		return (0);
	arg_n = check_flags(built, i);
	return (arg_n);
}

int	is_echo(char *s)
{
	if (ft_strlen(s) == 4)
	{
		if (s[0] == 'e' && s[1] == 'c' && s[2] == 'h' && s[3] == 'o')
			return (1);
	}
	return (0);
}

void	built_echo(char **built, t_data *data)
{
	int	i;
	int	arg_n;

	i = 1;
	arg_n = 0;
	g_exit_status = 0;
	arg_n = parsing_echo(built);
	while (built[i])
	{
		if (i > arg_n)
		{
			if (i == 1)
				ft_putstr_fd_write_protected(built[i], data->red.fd_output);
			else
				ft_putstr_fd(built[i], data->red.fd_output);
			if (built[i + 1])
				ft_putstr_fd(" ", data->red.fd_output);
		}
		i++;
	}
	if (!arg_n)
		ft_putstr_fd("\n", data->red.fd_output);
}

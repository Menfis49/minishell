/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 00:54:30 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 03:43:06 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit(char *s)
{
	if (ft_strlen(s) == 4)
	{
		if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't')
			return (1);
	}
	return (0);
}

int	check_if_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

int	exit_with_first_arg_numeric(char **ds, t_data *data)
{
	int	i;

	i = 0;
	if (ft_nb_str(ds) == 2)
	{
		i = ft_atoi(ds[1]);
		if (!data->pipe.nb_pipe_created)
			ft_putstr_fd("exit\n", 2);
		free_all(data);
		exit(i);
		return (0);
	}
	else
	{
		if (!data->pipe.nb_pipe_created)
			ft_putstr_fd("exit\n", 2);
		write_error("Minishell: exit: too many arguments");
		return (1);
	}
}

void	built_exit(t_data *data, char **ds)
{
	int	status;

	status = 0;
	if (ds)
	{
		if (ft_nb_str(ds) > 1)
		{
			if (check_if_numeric(ds[1]))
				status = exit_with_first_arg_numeric(ds, data);
			if (!data->pipe.nb_pipe_created && !check_if_numeric(ds[1]))
				ft_putstr_fd("exit\n", 2);
			if (!check_if_numeric(ds[1]))
			{
				write_triple_str_error("exit: ", ds[1],
					": numeric argument is needed");
				status = 2;
			}
			free_all(data);
			exit(status);
		}
	}
	if (!data->pipe.nb_pipe_created)
		ft_putstr_fd("exit\n", 2);
	free_all(data);
	exit(status);
}

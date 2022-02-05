/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:32:51 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 01:07:14 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//is_a_directory 126
void	exit_write_error(t_data *data, char *s, char *s1)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd("\n", 2);
	free_all(data);
	exit(126);
}

//command not found 127
void	exit_write_error_cmd(t_data *data, char *s, char *s1)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd("\n", 2);
	free_all(data);
	exit(127);
}

void	exit_write_perror(char *s, t_data *data)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	free_all(data);
	if (errno)
		perror(NULL);
	exit(errno);
}

//path unset
void	exit_write_double_perror(char *s, char *s1, t_data *data)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	free_all(data);
	if (errno)
		perror(NULL);
	exit(127);
}

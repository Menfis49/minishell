/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_perror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:38:07 by jholl             #+#    #+#             */
/*   Updated: 2022/02/01 04:05:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset et export
void	write_double_error_one(char *cmd, char *s)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 1;
}

void	write_perror(char *s)
{
	ft_putstr_fd(s, 2);
	perror(NULL);
	g_exit_status = errno;
}

//fd open
void	write_double_str_perror(char *s, char *s1)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(" ", 2);
	perror(NULL);
	g_exit_status = errno;
}

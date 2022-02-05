/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:12:10 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 21:19:14 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parsing error
void	write_error(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 2;
}

//cd
void	write_error_one(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 1;
}

void	write_delim_str_error(char *s, char *s1)
{
	ft_putstr_fd("Minishell: warning: here-document at line ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd("')\n", 2);
	free(s);
}

void	write_triple_str_error(char *s, char *s1, char *s2)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 2;
}

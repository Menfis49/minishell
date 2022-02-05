/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:23:25 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 21:23:49 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putstr_fd_write_protected(char *str, int fd)
{
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		perror("Minishell: write error:");
		g_exit_status = errno;
	}
}

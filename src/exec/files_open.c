/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:54:38 by jholl             #+#    #+#             */
/*   Updated: 2022/01/29 21:35:52 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f_open_rdonly(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		write_double_str_perror("Minishell: ", path);
	return (fd);
}

int	f_open_creat_rdwr_trunc(char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		write_double_str_perror("Minishell: ", path);
	return (fd);
}	

int	f_open_creat_rdwr_append(char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		write_double_str_perror("Minishell: ", path);
	return (fd);
}

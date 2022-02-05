/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:07:06 by jholl             #+#    #+#             */
/*   Updated: 2022/01/19 17:32:10 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcpy(char *dst, const char *src, int size)
{
	int	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i] && (i + 1) < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

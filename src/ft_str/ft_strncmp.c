/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 22:54:28 by jholl             #+#    #+#             */
/*   Updated: 2022/01/23 14:26:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ts1;
	unsigned char	*ts2;

	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	i = 0;
	while (ts1[i] && ts2[i] && i < n)
	{
		if (ts1[i] != ts2[i])
			return (ts1[i] - ts2[i]);
		i++;
	}
	if (i < n)
		return (ts1[i] - ts2[i]);
	return (0);
}

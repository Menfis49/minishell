/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:31:37 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:31:45 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_nblen(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*dest_malloc(int n, unsigned int len, t_data *data)
{
	char	*dest;

	if (n < 0)
		dest = malloc(sizeof(*dest) * (len + 2));
	else
		dest = malloc(sizeof(*dest) * (len + 1));
	if (!dest)
		exit_write_perror(MALLOC_ERROR, data);
	return (dest);
}

unsigned int	set_nb(int n)
{
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

char	*ft_itoa(int n, t_data *data)
{
	char			*dest;
	unsigned int	len;
	unsigned int	nb;
	unsigned int	i;

	nb = set_nb(n);
	len = ft_nblen(nb);
	i = 0;
	dest = dest_malloc(n, len, data);
	if (n < 0)
	{
		dest[i] = '-';
		len++;
	}
	i = len - 1;
	while (nb >= 10)
	{
		dest[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	dest[i] = nb % 10 + 48;
	dest[len] = '\0';
	return (dest);
}

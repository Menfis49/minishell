/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 04:29:18 by jholl             #+#    #+#             */
/*   Updated: 2022/01/20 14:39:57 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**arr_free(char **ptr, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static size_t	cnt_w(char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	arr_crt(char const *s, char c, char ***ptr_f)
{
	char	**ptr;

	if (!s)
		return (0);
	ptr = (char **)malloc((cnt_w((char *)s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	*ptr_f = ptr;
	return (1);
}

static int	ptr_k_substr(size_t i, size_t j, char **ptr, char const *s)
{
	*ptr = ft_substr((char *)s, j, i - j);
	if (!(*ptr))
		return (0);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!arr_crt(s, c, &ptr))
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[j])
			if (!ptr_k_substr(i, j, &ptr[k], s))
				return (arr_free(ptr, k));
		if (s[j])
			k++;
	}
	ptr[k] = NULL;
	return (ptr);
}

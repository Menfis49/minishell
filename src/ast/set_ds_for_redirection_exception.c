/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ds_for_redirection_exception.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:32:14 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:32:16 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_new_ds(char **new_ds, char **second, char **first)
{
	int	i;
	int	j;

	i = 0;
	while (first[i])
	{
		new_ds[i] = first[i];
		i++;
	}
	j = 1;
	while (second[j])
	{
		new_ds[i] = second[j];
		second[j] = NULL;
		i++;
		j++;
	}
	new_ds[i] = NULL;
}

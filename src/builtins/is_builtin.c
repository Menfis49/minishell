/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 01:28:24 by jholl             #+#    #+#             */
/*   Updated: 2022/01/28 01:33:28 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *built)
{
	if (is_echo(built) || is_pwd(built) || (is_env(built)) \
			|| (is_unset(built)) || (is_cd(built)) \
			|| (is_export(built)) || (is_exit(built)))
		return (1);
	return (0);
}

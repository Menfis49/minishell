/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:33:35 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 21:33:40 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redirections(t_data *data)
{
	if (data->red.fd_input != 0 && data->red.fd_input > 0)
	{
		close(data->red.fd_input);
		data->red.fd_input = 0;
	}
	if (data->red.fd_output != 1 && data->red.fd_output > 1)
	{
		close(data->red.fd_output);
		data->red.fd_output = 1;
	}
}

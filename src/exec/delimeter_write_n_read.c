/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter_write_n_read.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:28:19 by jholl             #+#    #+#             */
/*   Updated: 2022/01/31 18:17:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_var(int *j, int *ret)
{
	*j = 0;
	*ret = 1;
}

void	read_while_delimeter(t_token tok, t_data *data)
{
	int		i;
	int		j;
	int		ret;
	char	buff[4097];

	init_var(&j, &ret);
	while (1)
	{
		write(1, "> ", 1);
		ret = read(STDIN_FILENO, buff, 4096);
		if (ret == -1)
			exit_write_perror("Minishell: ", data);
		if (ret == 0)
		{
			write_delim_str_error(ft_itoa(j, data), tok.s[0]);
			return ;
		}
		i = 0;
		while (buff[i] == tok.s[0][i])
		{
			if (i + 1 == ft_strlen(tok.s[0]) && buff[i + 1] == '\n')
				return ;
			i++;
		}
	}
}

void	write_read_content(t_data *data, char *buff, int ret)
{
	if ((data->red.fd_input > 1) && (data->red.is_delimeter))
	{
		ret = write(data->red.fd_input, buff, ret);
		if (ret == -1)
			exit_write_perror("Minishell: write function: ", data);
	}
}

int	identify_delim(char *s, char *buff)
{
	int		i;

	i = 0;
	while (buff[i] == s[i])
	{
		if (i + 1 == ft_strlen(s) && buff[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	read_write_while_delimeter(t_token tok, t_data *data)
{
	int		j;
	int		ret;
	char	buff[4097];

	init_var(&j, &ret);
	while (1)
	{
		write(1, "> ", 1);
		ret = read(STDIN_FILENO, buff, 4096);
		if (ret == -1)
			exit_write_perror("Minishell: read function: ", data);
		if (ret == 0)
		{
			write_delim_str_error(ft_itoa(j, data), tok.s[0]);
			return ;
		}
		if (identify_delim(tok.s[0], buff))
			return ;
		write_read_content(data, buff, ret);
		j++;
	}
}

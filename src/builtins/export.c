/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:13:17 by jholl             #+#    #+#             */
/*   Updated: 2022/02/01 16:18:25 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_export(char *built)
{
	int	i;

	i = 0;
	if (!ft_is_alpha(built[0]))
	{
		if (built[0] == '$' && built[1] != '\0')
			return (1);
		return (0);
	}
	while (built[i])
	{
		if (built[i] == '=')
			return (1);
		i++;
	}
	return (2);
}

char	*find_var(char *str, t_data *data)
{
	char	*var;
	int		size_var;
	int		i;

	size_var = 0;
	i = 0;
	while (str[size_var] != '=')
		size_var++;
	var = malloc(sizeof(*var) * (size_var + 1));
	if (!var)
		exit_write_perror(MALLOC_ERROR, data);
	while (i < size_var)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*find_value(char *str, t_data *data)
{
	char	*value;
	int		size_value;
	int		size_var;
	int		i;
	int		j;

	size_value = 0;
	size_var = 0;
	i = 0;
	while (str[size_var] != '=')
		size_var++;
	j = size_var + 1;
	size_value = ft_strlen(str);
	size_value -= (size_var + 1);
	if (j == ft_strlen(str))
		return (NULL);
	value = malloc(sizeof(*value) * (size_value + 1));
	if (!value)
		exit_write_perror(MALLOC_ERROR, data);
	while (i < size_value)
		value[i++] = str[j++];
	value[i] = '\0';
	return (value);
}

void	treat_equal_export(char *s, t_data *data)
{
	char	*var;
	char	*value;

	var = find_var(s, data);
	value = find_value(s, data);
	set_env(data, var, value);
	free(var);
	free(value);
	g_exit_status = 0;
}

void	built_export(t_data *data, char **built)
{
	int		i;

	i = 1;
	if (!built[1])
		env_only_data(data);
	while (built[i])
	{	
		if (built[1][0] == '\0')
		{
			write_double_error_one("export: ", built[i]);
			g_exit_status = 1;
			return ;
		}
		if (!parsing_export(built[i]))
			write_double_error_one("export: ", built[i]);
		else if (parsing_export(built[i]) == 1)
			treat_equal_export(built[i], data);
		i++;
	}
}

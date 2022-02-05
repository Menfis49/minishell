/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 22:48:06 by jholl             #+#    #+#             */
/*   Updated: 2022/01/23 14:35:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_var(t_data *data, char **env)
{
	t_list	*new_node;
	char	*new_s;

	new_s = malloc(sizeof(char) * (ft_strlen(*env) + 1));
	if (!new_s)
		exit_write_perror(MALLOC_ERROR, data);
	ft_strlcpy(new_s, *env, ft_strlen(*env) + 1);
	new_node = ft_lstnew(new_s);
	if (!new_node)
		exit_write_perror(MALLOC_ERROR, data);
	if (!data->our_env)
		data->our_env = new_node;
	else
		ft_lstadd_back(&(data->our_env), new_node);
}

void	get_caller_env(t_data *data, char **env)
{
	data->our_env = NULL;
	while (*env)
	{
		add_env_var(data, env);
		env++;
	}
}

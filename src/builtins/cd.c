/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 15:11:48 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 13:38:44 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getcwd_success(t_data *data, char *pwd)
{
	char	*new;

	new = NULL;
	if (ft_list_find(data->our_env, "OLDPWD", &check_if_var_exist))
	{
		if (ft_list_find(data->our_env, "PWD", &check_if_var_exist))
		{
			new = lf_var("PWD", data);
			set_env(data, "OLDPWD", new);
			if (new)
				free(new);
		}
		else
			set_env(data, "OLDPWD", NULL);
	}
	if (ft_list_find(data->our_env, "PWD", &check_if_var_exist))
		set_env(data, "PWD", pwd);
	if (data->pwd)
		free(data->pwd);
	data->pwd = NULL;
	data->pwd = malloc(sizeof(char) * (ft_strlen(pwd) + 1));
	if (!data->pwd)
		exit_write_perror(MALLOC_ERROR, data);
	ft_strlcpy(data->pwd, pwd, ft_strlen(pwd) + 1);
}

void	getcwd_fail(t_data *data, char *path)
{
	char	*new;

	new = NULL;
	write_perror("Minishell: cd: ");
	new = ft_strjoin(data->old_pwd, "/");
	if (data->pwd)
		free(data->pwd);
	data->pwd = NULL;
	if (!new)
		exit_write_perror(MALLOC_ERROR, data);
	data->pwd = ft_strjoin(new, path);
	free(new);
	if (!data->pwd)
		exit_write_perror(MALLOC_ERROR, data);
	if (ft_list_find(data->our_env, "PWD", &check_if_var_exist))
		set_env(data, "PWD", data->pwd);
}

void	use_cd(char *path, t_data *data)
{
	char	pwd[1024];

	if (data->old_pwd)
		free(data->old_pwd);
	data->old_pwd = NULL;
	data->old_pwd = data->pwd;
	data->pwd = NULL;
	if (chdir(path) == -1)
	{
		write_perror("Minishell: cd: ");
	}
	else
	{
		if (!getcwd(pwd, 1024))
			getcwd_fail(data, path);
		else
			getcwd_success(data, pwd);
	}
}

int	is_cd(char *s)
{
	if (ft_strlen(s) == 2)
	{
		if (s[0] == 'c' && s[1] == 'd')
			return (1);
	}
	return (0);
}

void	built_cd(char **built, t_data *data)
{
	if (ft_nb_str(built) > 2)
		write_error_one("Minishell: cd: too many arguments.");
	else
	{
		if (built[1] == NULL)
		{
			write_error_one("Minishell: cd: need relative or absolute path.");
			return ;
		}
		use_cd(built[1], data);
	}
	g_exit_status = 0;
}

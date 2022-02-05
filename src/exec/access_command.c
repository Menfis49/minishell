/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholl <jholl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:23:33 by jholl             #+#    #+#             */
/*   Updated: 2022/02/02 01:04:45 by jholl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*stat_is_directory(char *path, t_data *data, char **path_split)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
	{
		if (path_split)
			free_dstr(path_split);
		exit_write_perror("stat function failed: ", data);
	}
	if (!S_ISDIR(buf.st_mode))
		return (path);
	else
	{
		if (path_split)
			free_dstr(path_split);
		exit_write_error(data, path, " Is a directory");
	}
	return (NULL);
}

void	free_and_exit_write_perror(char **path_split, t_data *data)
{
	free_dstr(path_split);
	exit_write_perror("ft_strjoin function failed: ", data);
}

char	*try_access_path(char **path_split, char *path_cmd, t_data *data)
{
	int			i;
	char		*test_path;
	char		*path;

	i = 0;
	while (path_split[i])
	{
		path = ft_strjoin(path_split[i], "/");
		if (!path)
			free_and_exit_write_perror(path_split, data);
		test_path = ft_strjoin(path, path_cmd);
		if (path)
		{
			free_str(path);
			path = NULL;
		}
		if (!test_path)
			free_and_exit_write_perror(path_split, data);
		if (access(test_path, X_OK) == 0)
			return (stat_is_directory(test_path, data, path_split));
		free_str(test_path);
		i++;
	}
	return (NULL);
}

int	lf_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*access_command(t_data *data, char *path_cmd)
{
	char		*path_env;
	char		**path_split;
	char		*path;

	if (path_cmd[0] == '\0')
		exit_write_error_cmd(data, path_cmd, ": command not found");
	if (access(path_cmd, X_OK) == 0)
		return (stat_is_directory(path_cmd, data, NULL));
	path_env = lf_var("PATH", data);
	if (!path_env)
		exit_write_double_perror("Minishell: ", path_cmd, data);
	path_split = ft_split(path_env, ':');
	if (path_env)
		free(path_env);
	path_env = NULL;
	if (!path_split)
		exit_write_perror("ft_split function failed: ", data);
	path = try_access_path(path_split, path_cmd, data);
	free_dstr(path_split);
	path_split = NULL;
	if (!path && lf_slash(path_cmd))
		exit_write_error_cmd(data, path_cmd, ": No such file or directory");
	if (!path)
		exit_write_error_cmd(data, path_cmd, ": command not found");
	return (path);
}

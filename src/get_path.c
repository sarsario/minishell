/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:14:32 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/30 08:38:33 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*path_join(char *path, char *name)
{
	char	*tmp;
	char	*fullpath;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
	{
		ft_putstr_fd("[minishell]: malloc error\n", 2);
		g_global_status = 1;
		return (NULL);
	}
	fullpath = ft_strjoin(tmp, name);
	free(tmp);
	if (!fullpath)
	{
		ft_putstr_fd("[minishell]: malloc error\n", 2);
		g_global_status = 1;
		return (NULL);
	}
	return (fullpath);
}

static char	*get_fullpath(char **paths, char *name)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = path_join(paths[i], name);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_putstr_fd("[minishell]: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_global_status = 127;
	return (NULL);
}

char	*get_path(char **envp, char *name)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
			{
				ft_putstr_fd("[minishell]: malloc error\n", 2);
				g_global_status = 1;
				return (NULL);
			}
			path = get_fullpath(paths, name);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	direct_path(t_child *data)
{
	int	i;

	i = 0;
	while (data->cmd->cmd[0][i])
	{
		if (data->cmd->cmd[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_direct_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:38:15 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/30 09:08:50 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*malloc_fail(char *to_free)
{
	if (to_free)
		free(to_free);
	ft_putstr_fd("[minishell]: malloc error\n", 2);
	g_global_status = 1;
	return (NULL);
}

static char	*access_error(t_child *data, char *to_free)
{
	char	*tmp;

	if (to_free)
		free(to_free);
	tmp = ft_strjoin("[minishell]: ", data->cmd->cmd[0]);
	if (!tmp)
		return (malloc_fail(NULL));
	perror(tmp);
	free(tmp);
	g_global_status = 127;
	return (NULL);
}

char	*get_direct_path(t_child *data)
{
	char	*path;
	char	*exe;
	char	*tmp;

	tmp = ft_strrchr(data->cmd->cmd[0], '/');
	if (!tmp || !tmp[1])
		return (malloc_fail(NULL));
	exe = ft_strdup(tmp + 1);
	if (!exe)
		return (malloc_fail(NULL));
	if (access(data->cmd->cmd[0], F_OK) == -1)
		return (access_error(data, exe));
	path = ft_strdup(data->cmd->cmd[0]);
	if (!path)
		return (malloc_fail(exe));
	free(data->cmd->cmd[0]);
	data->cmd->cmd[0] = exe;
	return (path);
}

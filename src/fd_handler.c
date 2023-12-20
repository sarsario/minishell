/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:18:06 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/27 11:41:11 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fd_perror(char *str)
{
	perror(ft_strjoin("[minishell]: ", str));
	return (-1);
}

int	fd_out_handler(t_child *data, char **r_out, char **r_app)
{
	int		i;
	int		fd;

	i = 1;
	fd = -2;
	while (i < data->cmd->order[0])
	{
		if (fd > -1 && (data->cmd->order[i] == 2 || data->cmd->order[i] == 4))
			close(fd);
		if (data->cmd->order[i] == 2)
		{
			fd = open(*(r_app++), O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (fd_perror(*(r_app - 1)));
		}
		if (data->cmd->order[i] == 4)
		{
			fd = open(*(r_out++), O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (fd_perror(*(r_out - 1)));
		}
		i++;
	}
	return (fd);
}

int	fd_in_handler(t_child *data)
{
	int		i;
	int		fd;
	char	**tmp;

	i = 1;
	fd = -2;
	tmp = data->cmd->redir_in;
	while (i < data->cmd->order[0])
	{
		if (fd > -1 && (data->cmd->order[i] == 1 || data->cmd->order[i] == 3))
			close(fd);
		if (data->cmd->order[i] == 1)
			fd = open(data->cmd->hdoc, O_RDONLY);
		if (data->cmd->order[i] == 1 && fd == -1)
			return (fd_perror(data->cmd->hdoc));
		if (data->cmd->order[i] == 3)
			fd = open(*(tmp++), O_RDONLY);
		if (fd == -1)
			return (fd_perror(*(tmp - 1)));
		i++;
	}
	return (fd);
}

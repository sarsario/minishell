/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:05:24 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/20 14:20:47 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	close_for_last(int **pipefd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd - 2)
	{
		if (close(pipefd[i][0]) == -1)
		{
			perror("[minishell]: close error");
			return (0);
		}
		if (close(pipefd[i][1]) == -1)
		{
			perror("[minishell]: close error");
			return (0);
		}
		i++;
	}
	if (close(pipefd[i][1]) == -1)
	{
		perror("[minishell]: close error");
		return (0);
	}
	return (1);
}

static void	dup_last_handler(t_child *data, int fd_in, int fd_out, int i)
{
	if (fd_in > -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(data->pipefd[i - 1][0]);
	}
	else
		dup2(data->pipefd[i - 1][0], STDIN_FILENO);
	if (fd_out > -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(data->pipefd[i - 1][1]);
	}
}

int	last_child(t_child *data, int i)
{
	int	fd_in;
	int	fd_out;

	if (!close_for_last(data->pipefd, data->nb_cmd))
		return (1);
	fd_in = fd_in_handler(data);
	if (fd_in == -1)
	{
		close(data->pipefd[i - 1][0]);
		return (1);
	}
	fd_out = fd_out_handler(data, data->cmd->redir_out, data->cmd->append);
	if (fd_out == -1)
	{
		close(data->pipefd[i - 1][0]);
		if (fd_in > -1)
			close(fd_in);
		return (1);
	}
	dup_last_handler(data, fd_in, fd_out, i);
	return (exec_single(data));
}

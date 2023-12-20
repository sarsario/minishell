/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:23:41 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/20 14:02:28 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mid_perror(void)
{
	perror("[minishell]: close error");
	return (0);
}

static int	close_for_mid(int **pipefd, int nb, int i)
{
	int	j;

	j = 0;
	while (j < nb - 1)
	{
		if (j != i - 1 && j != i)
		{
			if (close(pipefd[j][0]) == -1)
				return (mid_perror());
			if (close(pipefd[j][1]) == -1)
				return (mid_perror());
		}
		else if (j == i - 1)
		{
			if (close(pipefd[j][1]) == -1)
				return (mid_perror());
		}
		else if (j == i)
		{
			if (close(pipefd[j][0]) == -1)
				return (mid_perror());
		}
		j++;
	}
	return (1);
}

static void	dup_middle_handler(t_child *data, int fd_in, int fd_out, int i)
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
		close(data->pipefd[i][1]);
	}
	else
		dup2(data->pipefd[i][1], STDOUT_FILENO);
}

int	middle_child(t_child *data, int i)
{
	int	fd_in;
	int	fd_out;

	if (!close_for_mid(data->pipefd, data->nb_cmd, i))
		return (1);
	fd_in = fd_in_handler(data);
	if (fd_in == -1)
	{
		close(data->pipefd[i - 1][0]);
		close(data->pipefd[i][1]);
		return (1);
	}
	fd_out = fd_out_handler(data, data->cmd->redir_out, data->cmd->append);
	if (fd_out == -1)
	{
		close(data->pipefd[i - 1][0]);
		close(data->pipefd[i][1]);
		if (fd_in > -1)
			close(fd_in);
		return (1);
	}
	dup_middle_handler(data, fd_in, fd_out, i);
	return (exec_single(data));
}

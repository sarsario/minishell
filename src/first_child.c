/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 08:11:06 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/30 09:11:57 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_single(t_child *data)
{
	char	*path;
	char	*error_msg;

	if (is_builtin(data->cmd->cmd))
		return (exec_builtin(data));
	if (direct_path(data))
		path = get_direct_path(data);
	else
		path = get_path(*(data->envp), *(data->cmd->cmd));
	if (path == NULL)
		return (g_global_status);
	reset_sig(data->cmd->sa);
	execve(path, data->cmd->cmd, *(data->envp));
	sig_setup(data->cmd->sa);
	error_msg = ft_strjoin("minishell: ", *(data->cmd->cmd));
	if (!error_msg)
		perror(path);
	else
	{
		perror(error_msg);
		free(error_msg);
	}
	free(path);
	return (1);
}

static int	only_child(t_child *data)
{
	int		fd_in;
	int		fd_out;

	fd_in = fd_in_handler(data);
	fd_out = fd_out_handler(data, data->cmd->redir_out, data->cmd->append);
	if (fd_in == -1 || fd_out == -1)
		return (1);
	if (fd_in > -1)
		dup2(fd_in, 0);
	if (fd_out > -1)
		dup2(fd_out, 1);
	if (is_builtin(data->cmd->cmd))
		return (exec_builtin(data));
	return (exec_single(data));
}

void	dup_first_handler(t_child *data, int fd_in, int fd_out)
{
	if (fd_in > -1)
		dup2(fd_in, 0);
	if (fd_out > -1)
	{
		dup2(fd_out, 1);
		close(data->pipefd[0][1]);
	}
	else
		dup2(data->pipefd[0][1], 1);
}

int	close_for_first(int **pipefd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd - 1)
	{
		if (i == 0)
		{
			if (close(pipefd[i][0]) == -1)
			{
				perror("[minishell]: close");
				return (0);
			}
		}
		else
		{
			if (close(pipefd[i][0]) == -1 || close(pipefd[i][1]) == -1)
			{
				perror("[minishell]: close");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	first_child(t_child *data, int i)
{
	int	fd_in;
	int	fd_out;

	if (data->nb_cmd == 1)
		return (only_child(data));
	if (!close_for_first(data->pipefd, data->nb_cmd))
		return (1);
	fd_in = fd_in_handler(data);
	if (fd_in == -1)
	{
		close(data->pipefd[i][1]);
		return (1);
	}
	fd_out = fd_out_handler(data, data->cmd->redir_out, data->cmd->append);
	if (fd_out == -1)
	{
		if (fd_in > -1)
			close(fd_in);
		close(data->pipefd[i][1]);
		return (1);
	}
	dup_first_handler(data, fd_in, fd_out);
	return (exec_single(data));
}

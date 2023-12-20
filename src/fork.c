/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:07:31 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/28 10:08:20 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	*alloc_pids(int nb_cmd)
{
	int	*pids;

	pids = malloc(sizeof(int) * (nb_cmd));
	if (!pids)
	{
		ft_putstr_fd("[minishell]: malloc error\n", 2);
		return (NULL);
	}
	return (pids);
}

static int	fork_error(int **pipefd, int *pids, int i, int nb_cmd)
{
	ft_putstr_fd("[minishell]: fork error\n", 2);
	if (!pipefd)
	{
		free(pids);
		return (1);
	}
	close_pipes(pipefd, nb_cmd);
	i = 0;
	while (i < nb_cmd - 1)
		free(pipefd[i++]);
	free(pipefd);
	free(pids);
	return (1);
}

static int	child_exec(t_child *data, int i)
{
	if (i == 0)
		return (first_child(data, i));
	else if (i == data->nb_cmd - 1)
		return (last_child(data, i));
	else
		return (middle_child(data, i));
}

static int	mass_wait(int *pids, int nb_cmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			g_global_status = WEXITSTATUS(status);
		i++;
	}
	free(pids);
	return (g_global_status);
}

int	fork_exec(t_cmd *cmd, char ***envp, int **pipefd, int nb_cmd)
{
	t_child	child_data;
	int		i;
	int		*pids;

	pids = alloc_pids(nb_cmd);
	if (!pids)
		return (1);
	i = 0;
	while (cmd)
	{
		child_data.cmd = cmd;
		child_data.envp = envp;
		child_data.pipefd = pipefd;
		child_data.nb_cmd = nb_cmd;
		pids[i] = fork();
		if (pids[i] == -1)
			return (fork_error(pipefd, pids, i, nb_cmd));
		if (pids[i] == 0)
			exit(child_exec(&child_data, i));
		i++;
		cmd = cmd->next;
	}
	if (pipefd)
		close_pipes(pipefd, nb_cmd);
	return (mass_wait(pids, nb_cmd));
}

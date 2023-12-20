/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:06:44 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/28 10:42:14 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	pre_exec_builtin(t_cmd *cmd, char ***envp)
{
	t_child	data;

	data.cmd = cmd;
	data.envp = envp;
	return (exec_builtin(&data));
}

int	exec_cmds(t_cmd *cmd, char ***envp)
{
	int	**pipefd;
	int	nb_cmd;
	int	res;

	nb_cmd = count_cmds(cmd);
	if (!nb_cmd)
		return (0);
	if (nb_cmd == 1)
	{
		if (is_builtin(cmd->cmd))
			return (pre_exec_builtin(cmd, envp));
		return (fork_exec(cmd, envp, NULL, nb_cmd));
	}
	pipefd = init_pipes(nb_cmd);
	if (!pipefd)
		return (1);
	res = fork_exec(cmd, envp, pipefd, nb_cmd);
	free_2d_int(pipefd, nb_cmd);
	return (res);
}

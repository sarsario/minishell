/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:51:42 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/29 13:51:51 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char **strs)
{
	if (!strs)
		return (0);
	if (!ft_strncmp(strs[0], "cd", ft_max(ft_strlen(strs[0]), 2)))
		return (1);
	if (!ft_strncmp(strs[0], "echo", ft_max(ft_strlen(strs[0]), 4)))
		return (1);
	if (!ft_strncmp(strs[0], "env", ft_max(ft_strlen(strs[0]), 3)))
		return (1);
	if (!ft_strncmp(strs[0], "exit", ft_max(ft_strlen(strs[0]), 4)))
		return (1);
	if (!ft_strncmp(strs[0], "export", ft_max(ft_strlen(strs[0]), 6)))
		return (1);
	if (!ft_strncmp(strs[0], "pwd", ft_max(ft_strlen(strs[0]), 3)))
		return (1);
	if (!ft_strncmp(strs[0], "unset", ft_max(ft_strlen(strs[0]), 5)))
		return (1);
	return (0);
}

int	exec_builtin(t_child *data)
{
	if (!ft_strncmp(data->cmd->cmd[0], "cd", \
		ft_max(ft_strlen(data->cmd->cmd[0]), 2)))
		return (ft_cd(data->cmd->cmd, data->envp));
	if (!ft_strncmp(data->cmd->cmd[0], "echo", \
		ft_max(ft_strlen(data->cmd->cmd[0]), 4)))
		return (ft_echo(data->cmd->cmd));
	if (!ft_strncmp(data->cmd->cmd[0], "env", \
		ft_max(ft_strlen(data->cmd->cmd[0]), 3)))
		return (ft_env(data->cmd->cmd, data->envp));
	if (!ft_strncmp(data->cmd->cmd[0], "exit", \
		ft_max(ft_strlen(data->cmd->cmd[0]), 4)))
		return (ft_exit(data->cmd->cmd));
	if (!ft_strncmp(data->cmd->cmd[0], "export", \
		ft_max(ft_strlen(data->cmd->cmd[0]), 6)))
		return (ft_export(data->cmd->cmd, data->envp, 1, 0));
	if (!ft_strncmp(data->cmd->cmd[0], "pwd", \
		ft_max(ft_strlen(data->cmd->cmd[0]), 3)))
		return (ft_pwd());
	if (!ft_strncmp(data->cmd->cmd[0], "unset", \
		ft_max(ft_strlen(data->cmd->cmd[0]), 5)))
		return (ft_unset(data->cmd->cmd, data->envp));
	return (0);
}

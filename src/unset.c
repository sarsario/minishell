/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:37:07 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/28 12:13:57 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	loop(char **args, char ***envp, int x_arg, int x_env)
{
	while (args[x_arg])
	{
		while (envp[0][x_env] && \
		ft_strlen(args[x_arg]) < ft_strlen(envp[0][x_env])
		&& ft_strncmp(args[x_arg], envp[0][x_env], ft_strlen(args[x_arg])))
			x_env++;
		if (envp[0][x_env])
		{
			while (envp[0][x_env])
			{
				if (envp[0][x_env + 1])
					envp[0][x_env] = envp[0][x_env + 1];
				else
					envp[0][x_env] = 0;
				if (!envp[0][x_env])
					return ;
				x_env++;
			}
		}
		x_arg++;
	}
}

int	ft_unset(char **args, char ***envp)
{
	if (!args[1])
		return (0);
	loop(args, envp, 1, 0);
	return (0);
}

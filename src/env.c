/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:35:54 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/28 11:37:18 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(char **cmd, char ***envp)
{
	int	x;

	if (cmd[1])
	{
		ft_putstr_fd("Error: Wrong number of arguments with \"env\"\n", 2);
		g_global_status = 1;
		return (1);
	}
	x = 0;
	while (envp[0][x])
	{
		printf("%s\n", envp[0][x]);
		x++;
	}
	return (0);
}

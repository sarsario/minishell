/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:35:43 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/27 12:22:18 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ('0' <= arg[i] && arg[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_exit(char **arg)
{
	int	i;
	int	status;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
	if (i == 2)
	{
		if (is_num(arg[1]))
			return (write(1, "bash: exit: numeric argument required\n", 38));
		status = ft_atoi(arg[1]);
		while (status > 256 || status < -256)
			status = status % 256;
		g_global_status = status;
	}
	exit(g_global_status);
}

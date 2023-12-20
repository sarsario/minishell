/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:35:28 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/29 13:52:04 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **args)
{
	int	x;

	x = 1;
	if (args[1] && !ft_strncmp(args[1], "-n", ft_max(ft_strlen(args[1]), 2)))
		x++;
	while (args[x])
	{
		printf("%s ", args[x]);
		x++;
	}
	if (args[1] && !ft_strncmp(args[1], "-n", ft_max(ft_strlen(args[1]), 2)))
		return (0);
	printf("\n");
	return (0);
}

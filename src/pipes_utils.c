/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:04:01 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/15 10:27:20 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (cmd)
	{
		nb_cmd++;
		cmd = cmd->next;
	}
	return (nb_cmd);
}

void	free_2d_int(int **str, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
		free(str[i++]);
	free(str);
}

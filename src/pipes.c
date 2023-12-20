/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:01:39 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/15 11:12:17 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	**alloc_pipes(int nb_cmd)
{
	int	**pipefd;
	int	i;

	pipefd = malloc(sizeof(int *) * (nb_cmd - 1));
	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < nb_cmd - 1)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipefd[i])
		{
			ft_putstr_fd("[minishell]: malloc error\n", 2);
			while (--i >= 0)
				free(pipefd[i]);
			free(pipefd);
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}

static int	**multi_pipe(int **pipefd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd - 1)
	{
		if (pipe(pipefd[i]) == -1)
		{
			ft_putstr_fd("[minishell]: pipe error\n", 2);
			while (--i >= 0)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
			i = 0;
			while (i < nb_cmd - 1)
				free(pipefd[i++]);
			free(pipefd);
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}

void	close_pipes(int **pipefd, int nb)
{
	int	i;

	i = 0;
	while (i < nb - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

int	**init_pipes(int nb_cmd)
{
	int	**pipefd;

	pipefd = alloc_pipes(nb_cmd);
	if (!pipefd)
		return (NULL);
	pipefd = multi_pipe(pipefd, nb_cmd);
	if (!pipefd)
		return (NULL);
	return (pipefd);
}

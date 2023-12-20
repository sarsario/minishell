/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraydup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:18:13 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/30 10:35:44 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**arraydup(char **arg)
{
	int		i;
	int		j;
	char	**tmp;
	int		shlvl;

	i = 0;
	while (arg && arg[i])
		i++;
	tmp = malloc(sizeof(char *) * i + 1);
	while (--i >= 0)
		tmp[i] = ft_strdup(arg[i]);
	i = 0;
	while (ft_strlen(arg[i]) < 6 || \
	ft_strncmp("SHLVL", arg[i], ft_strlen("SHLVL")))
		i++;
	j = 0;
	while (arg[i][j] != '=')
		j++;
	j++;
	shlvl = ft_atoi(&arg[i][j]);
	shlvl++;
	arg[i][j] = '\0';
	tmp[i] = ft_strjoin(arg[i], ft_itoa(shlvl));
	return (tmp);
}

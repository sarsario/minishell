/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:36:22 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/28 13:44:01 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_env(char ***envp)
{
	int	i;

	i = 0;
	while (envp[0][i])
	{
		printf("declare -x %s\n", envp[0][i]);
		i++;
	}
}

static void	sort_env(char ***envp)
{
	char	*tmp;
	int		i;
	int		j;
	int		count;

	count = 0;
	tmp = 0;
	while (envp[0][count])
		count++;
	i = -1;
	while (++i < count)
	{
		j = 0;
		while (j < count)
		{
			if (ft_strncmp(envp[0][i], envp[0][j], ft_strlen(envp[0][i])) < 0)
			{
				tmp = envp[0][i];
				envp[0][i] = envp[0][j];
				envp[0][j] = tmp;
			}
			j++;
		}
	}
	print_env(envp);
}

static int	is_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
	{
		if (i == 0)
		{
			printf("bash: export: '%s': not a valid identifier\n", arg);
			g_global_status = 1;
			return (0);
		}
		return (i);
	}
	return (-1);
}

static int	check_doublon(char *arg, char ***envp)
{
	int	x_env;

	x_env = 0;
	while (envp[0][x_env])
	{
		if (!ft_strncmp(arg, envp[0][x_env], is_value(arg)))
		{
			envp[0][x_env] = ft_strdup(arg);
			return (1);
		}
		x_env++;
	}
	return (0);
}

int	ft_export(char **args, char ***envp, int x_arg, int x_env)
{
	if (!args[1])
	{
		sort_env(envp);
		return (0);
	}
	while (args[x_arg])
	{
		if (is_value(args[x_arg]) > 0)
		{
			if (!check_doublon(args[x_arg], envp))
			{
				x_env = 0;
				while (envp[0][x_env])
					x_env++;
				envp[0] = ft_realloc_2d(envp[0], x_env + 1);
				envp[0][x_env] = ft_strdup(args[x_arg]);
			}
		}
		if (is_value(args[x_arg]) == 0)
			return (1);
		x_arg++;
	}
	return (0);
}

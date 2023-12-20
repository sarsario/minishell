/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:43:05 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/28 13:43:47 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char **path, char ***envp)
{
	int		err;
	char	*pwd;
	char	*getenv_pwd;

	pwd = 0;
	pwd = getcwd(pwd, 0);
	getenv_pwd = ft_strjoin("export OLDPWD=", pwd);
	ft_export(ft_split(getenv_pwd, ' '), envp, 1, 0);
	if (!path[1])
		err = chdir(getenv("HOME"));
	else
		err = chdir(path[1]);
	if (err == -1)
	{
		printf("cd: %s: No such file or directory\n", path[0]);
		return (1);
	}
	pwd = 0;
	pwd = getcwd(pwd, 0);
	getenv_pwd = ft_strjoin("export PWD=", pwd);
	ft_export(ft_split(getenv_pwd, ' '), envp, 1, 0);
	return (0);
}

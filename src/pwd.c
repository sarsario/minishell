/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <abarbieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 08:36:48 by abarbieu          #+#    #+#             */
/*   Updated: 2023/11/27 14:47:19 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = 0;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		exit (1);
	}
	printf("%s\n", pwd);
	return (0);
}

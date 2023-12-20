/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 06:54:37 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/03 12:11:25 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_realloc(char *str, int size)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(size + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i] && i < size)
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_realloc_2d(char **str, int size)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(size + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (str[i] && i < size)
	{
		new[i] = ft_strdup(str[i]);
		if (!new[i])
		{
			free_2d(new);
			return (NULL);
		}
		i++;
	}
	free_2d(str);
	return (new);
}

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**add_str(char **arr, char *str)
{
	if (!arr)
	{
		arr = ft_calloc(2, sizeof(char *));
		if (!arr)
			return (NULL);
		arr[0] = str;
		return (arr);
	}
	arr = ft_realloc_2d(arr, ft_strlen_2d(arr) + 1);
	if (!arr)
		return (NULL);
	arr[ft_strlen_2d(arr)] = str;
	return (arr);
}

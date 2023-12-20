/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:25:24 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/03 15:36:17 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*realloc_int(int *arr, int size)
{
	int	*new;
	int	i;

	new = ft_calloc(size, sizeof(int));
	if (!new)
		return (NULL);
	new[0] = size;
	i = 1;
	while (i < size)
	{
		new[i] = arr[i];
		i++;
	}
	free(arr);
	return (new);
}

int	*add_int(int *arr, int n)
{
	int	*new;
	int	i;

	if (!arr)
	{
		new = ft_calloc(2, sizeof(int));
		if (!new)
			return (NULL);
		new[0] = 2;
		new[1] = n;
		return (new);
	}
	new = ft_calloc(arr[0] + 1, sizeof(int));
	if (!new)
		return (NULL);
	new[0] = arr[0] + 1;
	i = 1;
	while (i < arr[0])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = n;
	free(arr);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:38:02 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:41:52 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	size_t	lentot;
	char	*result;

	i = 0;
	j = 0;
	lentot = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * lentot + 1);
	if (!result)
		return (0);
	while ((size_t)i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	while ((size_t)j < ft_strlen(s2))
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:59:09 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:32:36 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str2[0] == '\0')
		return (((char *)str1));
	while (i < len && str1[i])
	{
		if (str1[i] == str2[0] && str1[i])
		{
			j = 0;
			while (str1[i + j] == str2[j] && (str2[j] && i + j < len))
				j++;
			if (j == ft_strlen(str2))
				return (((char *)str1) + i);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:44:06 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:39:27 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	i = 0;
	str1 = ((unsigned char *)s1);
	str2 = ((unsigned char *)s2);
	if (n <= 0)
		return (0);
	n -= 1;
	while (str1[i] == str2[i] && n--)
	{
		i++;
	}
	if (str1[i] > str2[i])
		return (str1[i] - str2[i]);
	if (str1[i] < str2[i])
		return (str1[i] - str2[i]);
	return (0);
}

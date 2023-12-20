/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:44:35 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:29:00 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*str;

	str = ((unsigned char *)s);
	i = 0;
	while (i < n)
	{
		if (str[i] == ((unsigned char)c))
		{
			return (&str[i]);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:22:15 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:32:33 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t size)
{
	if (size <= 0)
		return (0);
	while (((unsigned char)*str1) == ((unsigned char)*str2) && size--)
	{
		if (!*str1 || !*str2)
			return (0);
		str1++;
		str2++;
	}
	if (!size)
		return ((unsigned char)*--str1 - (unsigned char)*--str2);
	if (((unsigned char)*str1) > ((unsigned char)*str2))
		return (1);
	if (((unsigned char)*str1) < ((unsigned char)*str2))
		return (-1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:23:34 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:32:47 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*sub;

	i = 0;
	s_len = 0;
	while (start < ft_strlen(s) && (s_len < len && s[start + s_len]))
		s_len++;
	sub = malloc(sizeof(char) * (s_len + 1));
	if (!sub)
		return (0);
	if (start < ft_strlen(s))
	{
		while (i < len && s[i + start])
		{
			sub[i] = s[start + i];
			i++;
		}
	}
	sub[i] = '\0';
	return (sub);
}

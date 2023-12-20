/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:32:51 by abarbieu          #+#    #+#             */
/*   Updated: 2023/04/25 14:28:29 by abarbieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static int	ft_hex_len(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

static void	ft_put_hex(unsigned int nb, char format)
{
	if (nb >= 16)
	{
		ft_put_hex(nb / 16, format);
		ft_put_hex(nb % 16, format);
	}
	if (nb <= 9)
		ft_c((nb + '0'));
	else if (nb <= 15)
	{
		if (format == 'x')
			ft_c(nb - 10 + 'a');
		if (format == 'X')
			ft_c(nb - 10 + 'A');
	}
}

int	ft_hex(unsigned int nb, char format)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
		ft_put_hex(nb, format);
	return (ft_hex_len(nb));
}
/*
int main()
{
	ft_hex(42, 'x');
}*/

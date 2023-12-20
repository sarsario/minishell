/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:27:30 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:36:34 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static int	ft_convert(va_list lst, char format)
{
	int	tot_len;

	tot_len = 0;
	if (format == 'c')
		tot_len += ft_c(va_arg(lst, int));
	if (format == 's')
		tot_len += ft_str(va_arg(lst, char *));
	if (format == 'p')
		tot_len += ft_point(va_arg(lst, unsigned long long));
	if (format == 'd' || format == 'i')
		tot_len += ft_putnbr(va_arg(lst, int));
	if (format == 'u')
		tot_len += ft_put_un_int(va_arg(lst, unsigned int));
	if (format == 'x' || format == 'X')
		tot_len += ft_hex(va_arg(lst, unsigned int), format);
	if (format == '%')
	{
		ft_c('%');
		tot_len++;
	}
	return (tot_len);
}

static int	is_format(char c)
{
	int		i;
	char	*set;

	i = 0;
	set = "cspdiuxX%";
	while (set[i])
	{
		if (c == set[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		tot_len;
	va_list	lst;

	i = 0;
	tot_len = 0;
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%' && is_format(str[i + 1]) == TRUE)
		{
			tot_len += ft_convert(lst, str[i + 1]);
			i += 2;
		}
		else
		{
			ft_c(str[i]);
			tot_len++;
			i++;
		}
	}
	va_end(lst);
	return (tot_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:10:27 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:51:52 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static int	check_newline(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (FALSE);
	while (line[i])
	{
		if (line[i] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static char	*ft_line(char *stack)
{
	int		i;
	int		len;
	char	*line;

	if (!stack)
		return (0);
	i = 0;
	len = 0;
	while (stack[len] && stack[len] != '\n')
		len++;
	if (stack[len])
		len++;
	line = malloc(sizeof(*line) * (len + 1));
	if (!line)
		return (0);
	while (i < len)
	{
		line[i] = stack[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_free(char *str)
{
	free(str);
	return (0);
}

char	*ft_left(char *stack)
{
	int		i;
	int		j;
	char	*left;

	if (!stack)
		return (0);
	i = 0;
	j = 0;
	while (stack[i] && stack[i] != '\n')
		i++;
	if (!stack[i])
		return (ft_free(stack));
	i++;
	left = malloc(sizeof(char) * (ft_strlen_gnl(stack + i) + 1));
	if (!left)
		return (ft_free(stack));
	while (stack[i + j])
	{
		left[j] = stack[i + j];
		j++;
	}
	left[j] = '\0';
	free(stack);
	return (left);
}

char	*get_next_line(int fd)
{
	int					c_read;
	char				*line;
	static char			*stack = 0;
	char				buff[BUFFER_SIZE + 1];

	while (check_newline(stack) == FALSE)
	{
		c_read = read(fd, buff, BUFFER_SIZE);
		if (c_read == -1)
			return (ft_set_stack(&stack));
		if (c_read == 0)
			break ;
		buff[c_read] = '\0';
		stack = ft_join(stack, &line, buff);
		if (!stack)
			return (0);
		free(line);
	}
	line = ft_line(stack);
	if (!line)
		return (ft_set_stack(&stack));
	stack = ft_left(stack);
	if (stack && stack[0] == '\0')
		ft_set_stack(&stack);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:04:42 by abarbieu          #+#    #+#             */
/*   Updated: 2023/09/20 08:29:46 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_countword(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && (str[i] == c))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !(str[i] == c))
			i++;
	}
	return (count);
}

static int	ft_wordlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	return (i);
}

static char	*ft_word(char const *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_wordlen(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (0);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	freestring(char **string, int i)
{
	int	a;

	a = 0;
	while (a <= i)
		free(string[i++]);
	free(string);
}

char	**ft_split(char const *str, char c)
{
	char	**strings;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (ft_countword(str, c) + 1));
	if (strings == NULL)
		return (NULL);
	while (*str != '\0')
	{
		while (*str != '\0' && (*str == c))
			str++;
		if (*str != '\0')
			strings[i++] = ft_word(str, c);
		if (i > 0 && strings[i - 1] == NULL)
		{
			freestring(strings, i - 1);
			return (NULL);
		}
		while (*str && !(*str == c))
			str++;
	}
	strings[i] = 0;
	return (strings);
}

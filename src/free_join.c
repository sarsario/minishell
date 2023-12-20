/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:50:15 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/02 13:34:06 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*free_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

int	is_new_arg(t_token *token)
{
	if (token->status == GENERAL && token->type == WHITE_SPACE)
		return (TRUE);
	if (token->status == GENERAL && token->type == SPE_CHAR && \
		!ft_strncmp(token->content, "|", ft_strlen(token->content)))
		return (TRUE);
	if (token->status == GENERAL && token->type == SPE_CHAR && \
		!ft_strncmp(token->content, "<", ft_strlen(token->content)))
		return (TRUE);
	if (token->status == GENERAL && token->type == SPE_CHAR && \
		!ft_strncmp(token->content, ">", ft_strlen(token->content)))
		return (TRUE);
	if (token->status == GENERAL && token->type == SPE_CHAR && \
		!ft_strncmp(token->content, ">>", ft_strlen(token->content)))
		return (TRUE);
	if (token->status == GENERAL && token->type == SPE_CHAR && \
		!ft_strncmp(token->content, "<<", ft_strlen(token->content)))
		return (TRUE);
	return (FALSE);
}

char	*heredoc_flag(char *s, int q)
{
	char	*temp;

	if (q)
		temp = ft_strdup("Q");
	else
		temp = ft_strdup("G");
	if (!temp)
	{
		free(s);
		return (NULL);
	}
	s = free_join(s, temp);
	if (!s)
		return (NULL);
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:07:22 by osarsari          #+#    #+#             */
/*   Updated: 2023/11/20 13:02:17 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*prev_not_space(t_token *token)
{
	t_token	*prev;

	if (!token || !token->prev)
		return (NULL);
	prev = token->prev;
	while (prev && prev->type == WHITE_SPACE)
		prev = prev->prev;
	return (prev);
}

static t_token	*next_not_space(t_token *token)
{
	t_token	*next;

	if (!token || !token->next)
		return (NULL);
	next = token->next;
	while (next && next->type == WHITE_SPACE)
		next = next->next;
	return (next);
}

t_token	*count_pipe(t_token *token, int *nb_cmd)
{
	t_token	*prev;
	t_token	*next;
	t_token	*current;

	current = token;
	while (current)
	{
		prev = prev_not_space(current);
		next = next_not_space(current);
		if ((is_redirection(current) && (!next || !is_path_start(next))) \
			|| (current->type == SPE_CHAR && \
			!ft_strncmp(current->content, "|", ft_strlen(current->content)) && \
			(!prev || !next)))
		{
			*nb_cmd = -1;
			if (prev && prev->type == SPE_CHAR)
				return (prev);
			return (current);
		}
		if (current->type == SPE_CHAR && \
			!ft_strncmp(current->content, "|", ft_strlen(current->content)))
			*nb_cmd += 1;
		current = next_not_space(current);
	}
	return (current);
}

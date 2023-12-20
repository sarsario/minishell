/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:30:33 by osarsari          #+#    #+#             */
/*   Updated: 2023/10/14 13:52:08 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_op_space(char c, int (*ints)[3])
{
	if (!(*ints)[1] && !(*ints)[2] && \
		(ft_isspace(c) || c == '|' || c == '<' || c == '>'))
		return (1);
	return (0);
}

int	is_spe_char(t_token *token)
{
	if (token->content && !ft_strncmp(token->content, ">>", \
		ft_strlen(token->content)))
		return (1);
	else if (token->content && !ft_strncmp(token->content, "<<", \
		ft_strlen(token->content)))
		return (1);
	else if (token->content && !ft_strncmp(token->content, ">", \
		ft_strlen(token->content)))
		return (1);
	else if (token->content && !ft_strncmp(token->content, "<", \
		ft_strlen(token->content)))
		return (1);
	else if (token->content && !ft_strncmp(token->content, "|", \
		ft_strlen(token->content)))
		return (1);
	else if (token->content && !ft_strncmp(token->content, "\'", \
		ft_strlen(token->content)))
		return (1);
	else if (token->content && !ft_strncmp(token->content, "\"", \
		ft_strlen(token->content)))
		return (1);
	return (0);
}

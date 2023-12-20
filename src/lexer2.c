/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:36:32 by abarbieu          #+#    #+#             */
/*   Updated: 2023/10/26 12:24:27 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_status(t_token *token, int quote, int dquote)
{
	if (quote && !token->status)
		token->status = QUOTES;
	else if (dquote && !token->status)
		token->status = DQUOTES;
	else if (!token->status)
		token->status = GENERAL;
}

t_token	*next_token(t_token *token, char line_read)
{
	t_token	*temp;

	if (line_read)
	{
		temp = ft_calloc(1, sizeof(t_token));
		if (!temp)
			exit_lexer(token, 0, 1);
		token->next = temp;
		temp->prev = token;
		token = temp;
		return (token);
	}
	return (0);
}

void	set_token_type(t_token *token)
{
	while (token)
	{
		if (token->content && token->status == GENERAL && \
			is_spe_char(token))
			token->type = SPE_CHAR;
		else if (token->content && token->content[0] == '$' && \
			token->content[1] && (ft_isalnum(token->content[1]) == 1 || \
			token->content[1] == '?' \
			|| token->content[1] == '_') && token->status != QUOTES)
			token->type = ENV;
		else if (token->content && token->status == GENERAL && \
			ft_isspace(token->content[0]))
			token->type = WHITE_SPACE;
		else
			token->type = WORDS;
		token = token->next;
	}
}

int	dollar(char *line_read, int i)
{
	if (line_read[i] && (ft_isalnum(line_read[i]) == 1 || line_read[i] == '_'))
	{
		while (ft_isalnum(line_read[i]) == 1 || line_read[i] == '_')
			i++;
		return (i);
	}
	else if (line_read[i] == '?')
	{
		return (i + 1);
	}
	else
		return (i);
}

void	ft_quote(char line_read, int (*ints)[3], t_token *token)
{
	token->status = GENERAL;
	if (line_read == '\'' && !(*ints)[2] && !(*ints)[1])
	{
		(*ints)[1] = 1;
	}
	else if (line_read == '\"' && !(*ints)[1] && !(*ints)[2])
		(*ints)[2] = 1;
	else if (line_read == '\'' && (*ints)[1])
	{
		(*ints)[1] = 0;
		token->status = GENERAL;
	}
	else if (line_read == '\"' && (*ints)[2])
	{
		(*ints)[2] = 0;
		token->status = GENERAL;
	}
	else if ((*ints)[1] == 1)
		token->status = QUOTES;
	else if ((*ints)[2] == 1)
		token->status = DQUOTES;
}

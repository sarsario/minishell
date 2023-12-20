/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:40:55 by abarbieu          #+#    #+#             */
/*   Updated: 2023/10/26 12:24:01 by osarsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	token_condition(char *line_read, int i, int (*ints)[3])
{
	if (line_read[i] == '$')
		return (dollar(line_read, i + 1));
	else if ((line_read[i] == '>' && line_read[i + 1] \
		&& line_read[i + 1] == '>') || (line_read[i] == '<' && \
		line_read[i + 1] && line_read[i + 1] == '<'))
		return (i + 2);
	else if (line_read[i] && (line_read[i] == '>' || line_read[i] == '<' || \
			line_read[i] == '|') && !(*ints)[1] && !(*ints)[2])
		return (i + 1);
	else if ((*ints)[1])
		while (line_read[i] && line_read[i] != '\'')
			i++;
	else if ((*ints)[2])
		while ((line_read[i] && line_read[i] != '\"'
				&& line_read[i] != '$'))
			i++;
	else
		while (line_read[i] && (!is_op_space(line_read[i], ints) && \
			line_read[i] != '\'' && line_read[i] != '\"' && \
			line_read[i] != '$'))
			i++;
	return (i);
}

static t_token	*token_quote(char *line_read, int start, int (*ints)[3])
{
	t_token	*new;

	new = init_token();
	if (!new)
		return (NULL);
	ft_quote(line_read[start], ints, new);
	(*ints)[0]++;
	new->content = ft_substr(line_read, start, (*ints)[0] - start);
	if (!(new->content))
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static t_token	*token_spe_char(char *line_read, int start, int (*ints)[3])
{
	t_token	*new;

	new = init_token();
	if (!new)
		return (NULL);
	if (line_read[(*ints)[0]] == '>' && line_read[(*ints)[0] + 1] \
		&& line_read[(*ints)[0] + 1] == '>')
		(*ints)[0]++;
	else if (line_read[(*ints)[0]] == '<' && line_read[(*ints)[0] + 1] \
		&& line_read[(*ints)[0] + 1] == '<')
		(*ints)[0]++;
	(*ints)[0]++;
	new->content = ft_substr(line_read, start, (*ints)[0] - start);
	if (!(new->content))
	{
		free(new);
		return (NULL);
	}
	ft_status(new, (*ints)[1], (*ints)[2]);
	return (new);
}

static t_token	*token_words(char *line_read, int start, int (*ints)[3])
{
	t_token	*new;

	new = init_token();
	if (!new)
		return (NULL);
	(*ints)[0] = token_condition(line_read, (*ints)[0], ints);
	new->content = ft_substr(line_read, start, (*ints)[0] - start);
	if (!(new->content))
	{
		free(new);
		return (NULL);
	}
	ft_status(new, (*ints)[1], (*ints)[2]);
	return (new);
}

t_token	*tokenizer(char *line_read)
{
	int		ints[3];
	t_token	*first;
	t_token	*token;

	ints[0] = 0;
	ints[1] = 0;
	ints[2] = 0;
	first = NULL;
	while (line_read[ints[0]])
	{
		if ((line_read[ints[0]] == '\'' && !ints[2])
			|| (line_read[ints[0]] == '\"' && !ints[1]))
			token = token_quote(line_read, ints[0], &ints);
		else if (is_op_space(line_read[ints[0]], &ints))
			token = token_spe_char(line_read, ints[0], &ints);
		else
			token = token_words(line_read, ints[0], &ints);
		if (!token)
			return (free_token(first));
		token_add_back(&first, token);
	}
	set_token_type(first);
	return (first);
}

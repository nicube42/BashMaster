/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:27:27 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/20 00:24:17 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	ft_skip_blank(char *line, int i)
{
	while (ft_is_blank(line[i]) && line[i])
		i++;
	return (i);
}

int	redirection_to_char(char *input, int i, t_bash *sh, int only_count)
{
	int		j;
	int		i_first;
	char	*word;

	j = 0;
	i_first = i;
	while (input[i] == '<' || input[i] == '>')
	{
		i++;
		j++;
	}
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i])
	{
		i++;
		j++;
	}
	word = malloc (sizeof(char) * (i + 1));
	j = 0;
	i = i_first;
	while (input[i] == '<' || input[i] == '>')
	{
		word[j] = input[i];
		i++;
		j++;
	}
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i])
	{
		word[j] = input[i];
		i++;
		j++;
	}
	if (only_count == 1)
		sh->lexed_size++;
	else
	{
		sh->lexed[sh->lexed_current] = word;
		sh->lexed_current++;
	}
	return (i);
}

int	pipe_to_char(char *input, int i, t_bash *sh, int only_count)
{
	char	*word;

	(void) input;
	word = "|";
	i++;
	if (only_count == 1)
		sh->lexed_size++;
	else
	{
		sh->lexed[sh->lexed_current] = word;
		sh->lexed_current++;
	}
	return (i);
}

int	word_to_char(char *input, int i, t_bash *sh, int only_count)
{
	char	*word;
	int		j;
	int		i_save;

	j = 0;
	i_save = i;
	while (input[i] != '|' && input[i] != '<' && input[i] != '>'
		&& !ft_is_blank(input[i]))
		i++;
	word = malloc (sizeof(char) * (i + 1));
	i = i_save;
	while (input[i] != '|' && input[i] != '<' && input[i] != '>'
		&& !ft_is_blank(input[i]))
	{
		word[j] = input[i];
		i++;
		j++;
	}
	if (only_count == 1)
		sh->lexed_size++;
	else
	{
		sh->lexed[sh->lexed_current] = word;
		sh->lexed_current++;
	}
	return (i);
}

void	lexer_size(char *input, t_bash *sh)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			i = pipe_to_char(input, i, sh, 1);
		else if ((input[i] == '<' || input[i] == '>'))
			i = redirection_to_char(input, i, sh, 1);
		else if (ft_is_blank(input[i]))
			i = ft_skip_blank(input, i);
		else
			i = word_to_char(input, i, sh, 1);
	}
}

char	**lexer(char *input, t_bash *sh)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			i = pipe_to_char(input, i, sh, 0);
		else if ((input[i] == '<' || input[i] == '>'))
			i = redirection_to_char(input, i, sh, 0);
		else if (ft_is_blank(input[i]))
			i = ft_skip_blank(input, i);
		else
			i = word_to_char(input, i, sh, 0);
	}
	return (0);
}

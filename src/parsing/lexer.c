/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:27:27 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/28 09:50:58 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	ft_is_quote(char c)
{
	if (c == '"')
		return (1);
	if (c == '\'')
		return (2);
	return (0);
}

void	init_lexed_malloc(t_bash *sh)
{
	sh->lexed = malloc(sizeof(char *) * (sh->lexed_size + 1));
	if (!sh->lexed)
		clean_exit("Malloc error", sh);
	sh->is_quote = malloc(sizeof(int) * (sh->lexed_size));
	if (!sh->is_quote)
		clean_exit("Malloc error", sh);
}

void	lexer_size(char *input, t_bash *sh)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			i = pipe_to_char(input, i, sh, 1);
		else if (ft_is_quote(input[i]))
			i = quote_to_char(input, i, sh, 1);
		else if ((input[i] == '<' || input[i] == '>'))
			i = redirection_to_char(input, i, sh, 1);
		else if (ft_is_blank(input[i]))
			i = ft_skip_blank(input, i);
		else
			i = word_to_char(input, i, sh, 1);
	}
	init_lexed_malloc(sh);
}

char	**lexer(char *input, t_bash *sh)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			i = pipe_to_char(input, i, sh, 0);
		else if (ft_is_quote(input[i]))
			i = quote_to_char(input, i, sh, 0);
		else if ((input[i] == '<' || input[i] == '>'))
			i = redirection_to_char(input, i, sh, 0);
		else if (ft_is_blank(input[i]))
			i = ft_skip_blank(input, i);
		else
			i = word_to_char(input, i, sh, 0);
	}
	return (0);
}

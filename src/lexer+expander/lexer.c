/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:27:27 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/17 11:21:52 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

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

int	calculate_redir_to_char(char *input, int i, t_bash *sh)
{
	int	j;

	j = 0;
	(void) sh;
	while ((input[i] == '<' || input[i] == '>') && input[i])
	{
		i++;
		j++;
	}
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i])
	{
		j++;
		i++;
	}
	return (j);
}

void	stock_in_struct(t_bash *sh, char *word, int j, int only_count)
{
	if (only_count == 1)
	{
		free (word);
		sh->lexed_size++;
	}
	else
	{
		sh->lexed[sh->lexed_current] = ft_strdup(word);
		if (!sh->lexed[sh->lexed_current])
			clean_exit("Malloc error", sh);
		free (word);
		sh->lexed[sh->lexed_current][j] = '\0';
		sh->lexed_current++;
	}
}

int	get_substr_reallength(char *str, int start_idx)
{
	int	len;

	len = 0;
	while (str[start_idx + len] && str[start_idx + len] != '\'')
		len++;
	return (len);
}

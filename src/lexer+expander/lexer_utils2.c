/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:28:14 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/17 13:43:52 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	compute_word_len(char *input, int *i)
{
	int	in_quotes;
	int	i_save;

	in_quotes = 0;
	i_save = *i;
	while (input[*i] && (in_quotes || (!ft_is_separator(input[*i])
				&& !ft_is_blank(input[*i]))))
	{
		if (input[*i] == '"' && in_quotes == 0)
			in_quotes = 1;
		else if (input[*i] == '"' && in_quotes == 1)
			in_quotes = 0;
		(*i)++;
	}
	return (*i - i_save);
}

char	*allocate_word(int length, t_bash *sh)
{
	char	*word;

	word = malloc(sizeof(char) * (length + 1));
	if (!word)
		clean_exit("Malloc error", sh);
	return (word);
}

int	fill_word(char *input, int i_save,
	int only_count, t_bash *sh)
{
	int	in_quotes;
	int	j;

	j = 0;
	in_quotes = 0;
	while (input[i_save] && (in_quotes || (!ft_is_separator(input[i_save])
				&& !ft_is_blank(input[i_save]))))
	{
		if (ft_is_quote(input[i_save]) == 2 && only_count == 0
			&& input[i_save] != '"')
			sh->is_quote[sh->lexed_current] = 1;
		if (ft_is_quote(input[i_save]) > 0 && in_quotes == 0)
			in_quotes = 1;
		else if (ft_is_quote(input[i_save]) > 0 && in_quotes == 1)
			in_quotes = 0;
		else
			sh->word[j++] = input[i_save];
		i_save++;
	}
	sh->word[j] = '\0';
	stock_in_struct(sh, sh->word, j, only_count);
	return (i_save);
}

int	ft_is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

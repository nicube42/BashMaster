/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:36:30 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/17 13:53:03 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	redirection_to_char(char *input, int i, t_bash *sh, int only_count)
{
	int		j;
	char	*word;

	j = calculate_redir_to_char(input, i, sh);
	word = malloc (sizeof(char) * (j + 1));
	if (!word)
		clean_exit("Malloc error", sh);
	j = 0;
	while ((input[i] == '<' || input[i] == '>') && input[i])
		word[j++] = input[i++];
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>' && input[i] != '"'
		&& input[i] != '\'' && input[i])
		word[j++] = input[i++];
	word[j] = '\0';
	stock_in_struct(sh, word, j, only_count);
	return (i);
}

int	pipe_to_char(char *input, int i, t_bash *sh, int only_count)
{
	char	*word;

	(void) input;
	word = "|\0";
	i++;
	if (only_count == 1)
		sh->lexed_size++;
	else
	{
		sh->lexed[sh->lexed_current] = ft_strdup(word);
		if (!sh->lexed[sh->lexed_current])
			clean_exit("Malloc error", sh);
		sh->lexed_current++;
	}
	return (i);
}

int	word_to_char(char *input, int i, t_bash *sh, int only_count)
{
	char	*word;
	int		i_save;

	i_save = i;
	word = allocate_word(compute_word_len(input, &i), sh);
	sh->word = word;
	return (fill_word(input, i_save, only_count, sh));
}

int	quote_to_char(char *input, int i, t_bash *sh, int only_count)
{
	char	*word;
	int		j;
	int		i_save;
	char	starting_quote;

	j = 0;
	starting_quote = input[i];
	if (ft_is_quote(input[i]) == 2 && only_count == 0 && starting_quote != '"')
		sh->is_quote[sh->lexed_current] = 1;
	i++;
	i_save = i;
	while (input[i] && input[i] != starting_quote)
		i++;
	if (!input[i])
		return (i);
	word = malloc(sizeof(char) * ((i - i_save) + 1));
	if (!word)
		clean_exit("Malloc error", sh);
	i = i_save;
	while (input[i] && input[i] != starting_quote)
		word[j++] = input[i++];
	word[j] = 0;
	stock_in_struct(sh, word, j, only_count);
	i++;
	return (i);
}

void	replace_with_empty(t_bash *sh, t_exp *exp)
{
	free(exp->tmp);
	exp->tmp = NULL;
	replace_substring(&sh->lexed[exp->i], exp, sh);
}

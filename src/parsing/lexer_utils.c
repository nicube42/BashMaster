/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:36:30 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/28 10:19:44 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	calculate_redir_to_char(char *input, int i, t_bash *sh)
{
	int	j;

	j = 0;
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
		sh->lexed[sh->lexed_current][1] = '\0';
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
		&& !ft_is_blank(input[i]) && input[i])
		i++;
	word = malloc (sizeof(char) * ((i - i_save) + 1));
	if (!word)
		clean_exit("Malloc error", sh);
	i = i_save;
	while (input[i] != '|' && input[i] != '<' && input[i] != '>'
		&& !ft_is_blank(input[i]) && input[i])
		word[j++] = input[i++];
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
		sh->lexed[sh->lexed_current][i - i_save] = '\0';
		sh->lexed_current++;
	}
	return (i);
}

int	quote_to_char(char *input, int i, t_bash *sh, int only_count)
{
	char	*word;
	int		j;
	int		i_save;

	j = 0;
	if (ft_is_quote(input[i]) == 2 && only_count == 0)
		sh->is_quote[sh->lexed_current] = 1;
	i++;
	i_save = i;
	while (!ft_is_quote(input[i]) && input[i])
		i++;
	word = malloc (sizeof(char) * ((i - i_save) + 1));
	if (!word)
		clean_exit("Malloc error", sh);
	i = i_save;
	while (!ft_is_quote(input[i]) && input[i])
		word[j++] = input[i++];
	word[j] = 0;
	if (only_count == 1)
	{
		sh->lexed_size++;
		free (word);
		i++;
	}
	else
	{
		sh->lexed[sh->lexed_current] = ft_strdup(word);
		if (!sh->lexed[sh->lexed_current])
			clean_exit("Malloc error", sh);
		free (word);
		sh->lexed[sh->lexed_current][i - i_save] = '\0';
		i++;
		sh->lexed_current++;
	}
	return (i);
}

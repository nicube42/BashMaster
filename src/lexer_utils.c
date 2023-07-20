/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 00:36:30 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/20 01:39:52 by ndiamant         ###   ########.fr       */
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

int	calculate_redir_to_char(char *input, int i, t_bash *sh)
{
	int	j;

	j = 0;
	while (input[i++] == '<' || input[i] == '>')
		j++;
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i++])
		j++;
	return (j);
}

int	redirection_to_char(char *input, int i, t_bash *sh, int only_count)
{
	int		j;
	char	*word;

	j = calculate_redir_to_char(input, i, sh);
	word = malloc (sizeof(char) * (j + 1));
	//if (!word)
	//	clean_exit();
	j = 0;
	while (input[i] == '<' || input[i] == '>')
		word[j++] = input[i++];
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i])
		word[j++] = input[i++];
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
	//if (!word)
	//	clean_exit();
	i = i_save;
	while (input[i] != '|' && input[i] != '<' && input[i] != '>'
		&& !ft_is_blank(input[i]))
		word[j++] = input[i++];
	if (only_count == 1)
		sh->lexed_size++;
	else
	{
		sh->lexed[sh->lexed_current] = word;
		sh->lexed_current++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:27:27 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/20 00:36:45 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:27:27 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/18 19:46:59 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

char	**lexer(char *input)
{
	int		i;
	int		j;
	int		k;
	char	**parsed;

	i = 0;
	j = 0;
	k = 0;
	parsed = 0;
	while (input[i])
	{
		if (input[i -  1] == '|')
		{
			j++;
			k = 0;
			printf("\n");
		}
		if (input[i] == ' ')
		{
			j++;
			k = 0;
			printf("\n");
		}
		else
		{
			printf("%c", input[i]);
		}
		if ((input[i + 1] == '|' || input[i + 1] == '<'
				|| input[i + 1] == '>') && input[i] != ' '
			&& input[i] != '<' && input[i] != '>')
		{
			j++;
			k = 0;
			printf("\n");
		}
		k++;
		i++;
	}
	return (parsed);
}

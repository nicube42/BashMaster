/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:27:27 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/18 18:42:39 by ndiamant         ###   ########.fr       */
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
		k++;
		i++;
	}
	return (parsed);
}

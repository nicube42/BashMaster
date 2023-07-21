/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 03:55:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/21 11:10:34 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

void	parser(t_bash *sh)
{
	int		i;
	int		j;
	t_list	*to_add;

	i = 0;
	sh->first = NULL;
	while (sh->lexed[i])
	{
		if (sh->lexed[i][0] == '<' || sh->lexed[i][0] == '>')
		{
			to_add = ft_init_token();
			to_add->value = sh->lexed[i];
			to_add->fd_in = 0;
			to_add->fd_out = 0;
			to_add->arguments = 0;
			to_add->id = 0;
			ft_add_token(sh, to_add);
			i++;
		}
		else if (sh->lexed[i][0] == '|')
		{
			to_add = ft_init_token();
			to_add->value = sh->lexed[i];
			to_add->fd_in = 0;
			to_add->fd_out = 0;
			to_add->arguments = 0;
			to_add->id = 0;
			ft_add_token(sh, to_add);
			i++;
		}
		else
		{
			j = i;
			to_add = ft_init_token();
			to_add->value = sh->lexed[i];
			to_add->fd_in = 0;
			to_add->fd_out = 0;
			while (sh->lexed[j][0] != '<' && sh->lexed[j][0] != '>'
				&& sh->lexed[j][0] != '|' && sh->lexed[j])
				j++;
			to_add->arguments = malloc (sizeof(char *) * j + 1);
			j = 0;
			i++;
			while (sh->lexed[i][0] != '<' && sh->lexed[i][0] != '>'
				&& sh->lexed[i][0] != '|' && sh->lexed[i])
			{
				to_add->arguments[j] = sh->lexed[i];
				i++;
				j++;
			}
			to_add->arguments[j] = 0;
			to_add->id = 0;
			ft_add_token(sh, to_add);
		}
	}
	ft_print_tokens(sh);
}

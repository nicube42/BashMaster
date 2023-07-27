/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:34:40 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/27 11:31:22 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

t_list	*ft_init_token(void)
{
	t_list	*token;

	token = (t_list *)malloc(sizeof(t_list));
	if (!token)
		return (0);
	token->prev = 0;
	token->next = 0;
	token->id = 0;
	return (token);
}

void	ft_add_token(t_bash *sh, t_list *to_add)
{
	t_list	*tmp;

	if (!sh->first)
		sh->first = to_add;
	else
	{
		tmp = sh->first;
		while (tmp->next)
			tmp = tmp->next;
		ft_connect_token(tmp, to_add);
	}
}

void	ft_connect_token(t_list *list, t_list *to_add)
{
	list->next = to_add;
	to_add->prev = list;
}

void	ft_print_tokens(t_bash *sh)
{
	t_list	*list;
	int		i;
	int		j;

	i = 1;
	list = sh->first;
	while (list)
	{
		j = 0;
		printf("value number %d : %s\n", i, list->value);
		if (list->arguments != 0)
		{
			while (list->arguments[j])
			{
				printf("      arguments %d : %s\n", j + 1, list->arguments[j]);
				j++;
			}
		}
		printf("id = %d\n", list->id);
		i++;
		printf("\n");
		list = list->next;
	}
}

void	destroy_tokens(t_bash *sh)
{
	t_list	*list;
	int		i;

	i = -1;
	list = sh->last;
	while (list)
	{
		if (list->arguments != 0)
		{
			while (list->arguments[++i])
			{
				free (list->arguments[i]);
				list->arguments = 0;
			}
		}
		free (list->value);
		free (list);
		list = list->prev;
	}
	i = -1;
	while (sh->splitted_path[++i])
		free (sh->splitted_path[i]);
	free (sh->splitted_path);
	free (sh->is_quote);
}

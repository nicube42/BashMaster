/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:34:40 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/28 10:00:58 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

t_list	*ft_init_token(t_bash *sh)
{
	t_list	*token;

	token = (t_list *)malloc(sizeof(t_list));
	if (!token)
		clean_exit("Malloc error", sh);
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
	t_list	*temp;
	char	**args;
	int		i;

	list = sh->first;
	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->value != 0)
			free(temp->value);
		if (temp->arguments != 0) 
		{
			args = temp->arguments;
			while (*args != 0)
			{
				free(*args);
				args++;
			}
			free(temp->arguments);
		}
		free(temp);
	}
	free_lexed(sh);
	i = -1;
	while (sh->splitted_path[++i])
		free (sh->splitted_path[i]);
	free (sh->splitted_path);
	if (sh->is_quote)
		free (sh->is_quote);
	free (sh->input);
}

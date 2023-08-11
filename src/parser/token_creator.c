/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:34:40 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 15:31:37 by ndiamant         ###   ########.fr       */
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
	token->fd_in = 0;
	token->fd_out = 0;
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

static void	destroy_tokens_2(t_bash *sh)
{
	t_list	*list;
	t_list	*temp;
	char	**args;

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
}

void	destroy_tokens(t_bash *sh)
{
	int		i;

	destroy_tokens_2(sh);
	free_lexed(sh);
	i = -1;
	if (sh->splitted_path)
	{
		while (sh->splitted_path[++i])
			free (sh->splitted_path[i]);
		free (sh->splitted_path);
	}
	if (sh->is_quote)
		free (sh->is_quote);
	if (sh->input)
		free (sh->input);
}

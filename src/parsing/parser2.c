/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:32:18 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 11:26:48 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static void	correct_here_doc(t_list *list)
{
	char	*tmp;

	if (list->id == HERE_DOC_TOKEN)
	{
		tmp = ft_substr(list->value, 2, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

static void	correct_red_entry(t_list *list)
{
	char	*tmp;

	if (list->id == RED_ENTRY_TOKEN)
	{
		tmp = ft_substr(list->value, 1, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

static void	correct_red_exit(t_list *list)
{
	char	*tmp;

	if (list->id == RED_EXIT_TOKEN)
	{
		tmp = ft_substr(list->value, 1, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

static void	correct_append(t_list *list)
{
	char	*tmp;

	if (list->id == APPEND_TOKEN)
	{
		tmp = ft_substr(list->value, 2, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

void	correct_redir(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	while (list)
	{
		correct_here_doc(list);
		correct_red_entry(list);
		correct_red_exit(list);
		correct_append(list);
		list = list->next;
	}
}

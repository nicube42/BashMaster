/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:37:06 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 15:40:57 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static void	print_pipe_error(void)
{
	printf(RED "No command before pipe\n" RESET);
}

static int	check_before_pipe(t_list *list)
{
	while (list)
	{
		if (list->id != CMD_TOK && list->id != BUILTIN_TOK
			&& list->id != HERE_DOC_TOKEN)
		{
			if (list->next && list->next->id == PIPE_TOK)
			{
				print_pipe_error();
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	pipe_syntax_error(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	if (list->id == PIPE_TOK)
	{
		print_pipe_error();
		return (1);
	}
	return (check_before_pipe(list));
}

static int	check_after_pipe(t_list *list)
{
	while (list)
	{
		if (list->id == PIPE_TOK && list->next)
		{
			list = list->next;
			if (list->id != CMD_TOK && list->id != BUILTIN_TOK
				&& list->id != PIPE_ERROR && list->id != HERE_DOC_TOKEN)
			{
				printf(RED "No command after pipe\n" RESET);
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	pipe_syntax_error_2(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	if (check_after_pipe(list))
		return (1);
	while (list->next)
		list = list->next;
	if (list->id == PIPE_TOK)
	{
		printf(RED "No command after pipe\n" RESET);
		return (1);
	}
	return (0);
}

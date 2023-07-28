/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:27:44 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/28 10:57:08 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	check_syntax(t_bash *sh)
{	
	if (unclosed_quote_error(sh))
		return (0);
	if (pipe_syntax_error(sh))
		return (0);
	if (pipe_syntax_error_2(sh))
		return (0);
	if (wrong_cmd_error(sh))
		return (0);
	return (1);
}

int	pipe_syntax_error(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	if (list->id == PIPE_TOK)
	{
		printf(RED "No command before pipe\n"RESET);
		return (1);
	}
	while (list)
	{
		if (list->id != CMD_TOK && list->id != BUILTIN_TOK)
		{
			if (list->next)
			{
				list = list->next;
				if (list->id == PIPE_TOK)
				{
					printf(RED "No command before pipe\n"RESET);
					return (1);
				}
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
	while (list)
	{
		if (list->id == PIPE_TOK && list->next)
		{
			list = list->next;
			if (list->id != CMD_TOK && list->id != BUILTIN_TOK)
			{
				printf(RED "No command after pipe\n"RESET);
				return (1);
			}
		}
		list = list->next;
	}
	list = sh->first;
	while (list->next)
		list = list->next;
	if (list->id == PIPE_TOK)
	{
		printf(RED "No command after pipe\n"RESET);
		return (1);
	}
	return (0);
}

int	unclosed_quote_error(t_bash *sh)
{
	if (sh->dquote_count % 2 == 1 && sh->dquote_count != 0)
	{
		printf(RED "Unclosed double quote detected\n" RESET);
		return (1);
	}
	if (sh->quote_count % 2 == 1 && sh->quote_count != 0)
	{
		printf(RED "Unclosed quote detected\n" RESET);
		return (1);
	}
	return (0);
}

int	wrong_cmd_error(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	while (list)
	{
		if (list->id == CMD_TOK)
		{
			if (ft_check_cmd(list->value, sh))
			{
				printf(RED "Unrecognised command : %s\n"RESET, list->value);
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

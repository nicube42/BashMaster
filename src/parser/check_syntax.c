/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:27:44 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 16:48:59 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	check_syntax(t_bash *sh)
{	
	if (unclosed_quote_error(sh))
		return (0);
	if (sh->lexed_size <= 0)
		return (0);
	if (pipe_syntax_error(sh))
		return (0);
	if (pipe_syntax_error_2(sh))
		return (0);
	if (wrong_cmd_error(sh))
		return (0);
	return (1);
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

static int	check_cmd_error(t_list *list, t_bash *sh)
{
	while (list)
	{
		if (list->id == CMD_TOK)
		{
			if (list->value[0] == '/' || (list->value[0] == '.'
					&& (list->value[1] == '/' || (list->value[1] == '.'
							&& list->value[2] == '/'))))
			{
				if (access(list->value, F_OK | X_OK) != 0)
					return (1);
			}
			else if (ft_check_cmd(list->value, sh))
				return (1);
		}
		list = list->next;
	}
	return (0);
}

int	wrong_cmd_error(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	sh->last_exit_status = 127;
	if (check_cmd_error(list, sh))
	{
		printf(RED "Unrecognized command : %s\n" RESET, list->value);
		return (1);
	}
	return (0);
}

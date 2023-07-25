/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:59:08 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/25 19:16:03 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	execute(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	while (list)
	{
		if (list->id == BUILTIN_TOK)
			execute_buildin(list, sh);
		list = list->next;
	}
}

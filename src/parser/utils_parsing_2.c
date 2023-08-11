/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:15:04 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 15:34:57 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	ft_is_quote(char c)
{
	if (c == '"')
		return (1);
	if (c == '\'')
		return (2);
	return (0);
}

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	ft_skip_blank(char *line, int i)
{
	while (ft_is_blank(line[i]) && line[i])
		i++;
	return (i);
}

void	set_last_of_list(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	while (list)
		list = list->next;
	sh->last = list;
}

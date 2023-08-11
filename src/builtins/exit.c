/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:07:52 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 14:08:15 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static int	is_all_digits(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	execute_exit(t_bash *sh, t_list *list)
{
	int	err_val;

	err_val = 0;
	if (list->arguments && list->arguments[0])
	{
		if (list->arguments[1])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			return ;
		}
		if (!is_all_digits(list->arguments[0]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			return ;
		}
		err_val = ft_atoi(list->arguments[0]);
		destroy_tokens(sh);
		exit(err_val);
	}
	destroy_tokens(sh);
	free_envp(sh);
	exit(0);
}

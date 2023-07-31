/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:57:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/30 11:41:01 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	execute_env(t_bash *sh)
{
	int	i;

	i = -1;
	while (sh->envp[++i])
		ft_printf("%s\n", sh->envp[i]);
}

void	execute_echo(t_list *list)
{
	int	i;

	i = -1;
	while (list->arguments[++i])
		if (ft_strncmp(list->arguments[i], "-n", 2) || i != 0)
			ft_printf("%s ", list->arguments[i]);
	if (list->arguments)
		if (ft_strncmp(list->arguments[0], "-n", 2))
			ft_printf("\n");
}

void	execute_pwd(t_bash *sh)
{
	int		i;
	char	*pwd;

	i = -1;
	while (sh->envp[++i])
	{
		if (!ft_strncmp("PWD", sh->envp[i], 3)
			&& sh->envp[i][3] == '=')
		{
			pwd = ft_substr(sh->envp[i],
					ft_strlen("pwd") + 1, ft_strlen(sh->envp[i]));
			if (!pwd)
				clean_exit("Malloc error", sh);
			break ;
		}
	}
	ft_printf("%s\n", pwd);
}

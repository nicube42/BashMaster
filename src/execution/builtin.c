/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:54:37 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/25 19:27:09 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	execute_buildin(t_list *list, t_bash *sh)
{
	if (!ft_strncmp(list->value, "pwd", 4))
		execute_pwd(sh);
	if (!ft_strncmp(list->value, "echo", 5))
		execute_echo(list);
	if (!ft_strncmp(list->value, "env", 4))
		execute_env(sh);
}

void	execute_env(t_bash *sh)
{
	int		i;

	i = -1;
	while (sh->envp[++i])
		ft_printf("%s\n", sh->envp[i]);
}

void	execute_echo(t_list *list)
{
	int	i;

	i = -1;
	while (list->arguments[++i])
		ft_printf("%s ", list->arguments[i]);
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
					ft_strlen(pwd), ft_strlen(sh->envp[i]));
			break ;
		}
	}
	ft_printf("%s\n", pwd);
}

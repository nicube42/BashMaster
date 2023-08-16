/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:05:08 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 19:25:43 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	execute_buildin(t_list *list, t_bash *sh)
{
	if (!ft_strncmp(list->value, "pwd", 4))
		execute_pwd(sh, list);
	if (!ft_strncmp(list->value, "echo", 5))
		execute_echo(list);
	if (!ft_strncmp(list->value, "env", 4))
		execute_env(sh, list);
	if (!ft_strncmp(list->value, "export", 5))
		execute_export(sh, list);
	if (!ft_strncmp(list->value, "unset", 6))
		execute_unset(list);
	exit (0);
}

void	execute_env(t_bash *sh, t_list *list)
{
	int	i;

	if (list->arguments[0])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return ;
	}
	i = -1;
	while (sh->envp[++i])
		printf("%s\n", sh->envp[i]);
}

void	execute_echo(t_list *list)
{
	int	i;

	i = -1;
	if (!list->arguments[0])
	{
		printf("\n");
		return ;
	}
	while (list->arguments[++i])
	{
		if (i > 1)
			printf(" ");
		if (ft_strncmp(list->arguments[0], "-n", 2) && i == 1)
			printf(" ");
		if (ft_strncmp(list->arguments[i], "-n", 2) || i != 0)
			printf("%s", list->arguments[i]);
	}
	if (list->arguments)
		if (ft_strncmp(list->arguments[0], "-n", 2))
			printf("\n");
}

void	execute_pwd(t_bash *sh, t_list *list)
{
	int		i;
	char	*pwd;

	i = -1;
	pwd = NULL;
	if (list->arguments[0])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
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
	printf("%s\n", pwd);
	free (pwd);
}

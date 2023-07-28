/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:54:37 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/28 10:06:01 by ndiamant         ###   ########.fr       */
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
	if (!ft_strncmp(list->value, "exit", 5))
		execute_exit(sh);
	if (!ft_strncmp(list->value, "export", 5))
		execute_export(sh, list);
	if (!ft_strncmp(list->value, "unset", 6))
		execute_unset(list);
}

void	execute_unset(t_list *list)
{
	if (!list->arguments[0])
		ft_printf(RED"unset: not enough arguments\n"RESET);
}

void	sort_environ(char **environ)
{
	char	**i;
	char	**j;
	char	*tmp;

	i = environ;
	while (*i)
	{
		j = i + 1;
		while (*j)
		{
			if (ft_strncmp(*i, *j, 1) > 0)
			{
				tmp = *i;
				*i = *j;
				*j = tmp;
			}
			j++;
		}
	i++;
	}
}

void	execute_export(t_bash *sh, t_list *list)
{
	char	**export;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (sh->envp[j])
		j++;
	export = malloc (sizeof(char *) * (j + 1));
	if (!export)
		clean_exit("Malloc error", sh);
	while (sh->envp[++i])
	{
		export[i] = ft_strdup(sh->envp[i]);
		if (!export[i])
			clean_exit("Malloc error", sh);
	}
	export[i] = 0;
	i = -1;
	sort_environ(export);
	if (!list->arguments[0])
		while (export[++i])
			printf("%s\n", export[i]);
}

void	execute_exit(t_bash *sh)
{
	destroy_tokens(sh);
	exit (0);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:19:47 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/09 12:49:32 by ndiamant         ###   ########.fr       */
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
		printf(RED"unset: not enough arguments\n"RESET);
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

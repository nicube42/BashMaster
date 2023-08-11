/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:19:47 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/11 11:00:44 by ndiamant         ###   ########.fr       */
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

void	execute_unset(t_list *list)
{
	if (!list->arguments[0])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return ;
	}
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
	{
		while (export[++i])
		{
			printf("%s\n", export[i]);
			free (export[i]);
		}
		free (export);
	}
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export+unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:08:57 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 21:29:10 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	execute_unset(t_list *list)
{
	if (!list->arguments[0])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return ;
	}
}

int	is_valid_format(char *arg)
{
	int	i;

	if (!arg || arg[0] == '\0' || arg[0] == '=')
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		return (1);
	return (0);
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

static char	**init_export_array(t_bash *sh)
{
	char	**export;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (sh->envp[j])
		j++;
	export = malloc(sizeof(char *) * (j + 1));
	if (!export)
		clean_exit("Malloc error", sh);
	while (sh->envp[++i])
	{
		export[i] = ft_strdup(sh->envp[i]);
		if (!export[i])
			clean_exit("Malloc error", sh);
	}
	export[i] = 0;
	return (export);
}

void	execute_export(t_bash *sh, t_list *list)
{
	char	**export;
	int		i;

	i = -1;
	export = init_export_array(sh);
	sort_environ(export);
	if (!list->arguments[0])
	{
		while (export[++i])
		{
			printf("%s\n", export[i]);
			free(export[i]);
		}
		free(export);
	}
}

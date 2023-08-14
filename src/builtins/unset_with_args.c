/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_with_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:44:34 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/14 23:27:06 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

static void	remove_env(t_bash *sh, int env_index)
{
	char	**new_envp;
	int		size;
	int		i;
	int		j;

	size = 0;
	while (sh->envp[size])
		size++;
	new_envp = (char **)malloc(sizeof(char *) * size);
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (i != env_index)
		{
			new_envp[j] = sh->envp[i];
			j++;
		}
		else
			free(sh->envp[i]);
	}
	new_envp[j] = NULL;
	free(sh->envp);
	sh->envp = new_envp;
}

void	unset_cmd(t_bash *sh, char *arg)
{
	int		env_index;

	env_index = find_key(sh, arg);
	if (env_index >= 0)
		remove_env(sh, env_index);
}

void	handle_unset(t_bash *sh, char **args)
{
	int		i;

	i = 0;
	if (!args[0])
	{
		sh->last_exit_status = 0;
		return ;
	}
	while (args[i])
	{
		unset_cmd(sh, args[i]);
		i++;
	}
	sh->last_exit_status = 0;
}

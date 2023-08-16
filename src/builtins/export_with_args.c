/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:40:59 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/16 21:29:00 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

int	find_key(t_bash *sh, char *key)
{
	int		index;
	int		key_len;

	index = 0;
	key_len = ft_strlen(key);
	while (sh->envp[index])
	{
		if (!ft_strncmp(sh->envp[index], key, key_len)
			&& sh->envp[index][key_len] == '=')
			return (index);
		index++;
	}
	return (-1);
}

static char	*get_key(char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = (char *)malloc(i + 2);
	ft_strlcpy(key, arg, i + 1);
	key[i + 1] = '\0';
	return (key);
}

static void	add_env(t_bash *sh, char *arg)
{
	int		size;
	char	**new_envp;
	int		i;

	size = 0;
	i = -1;
	while (sh->envp[size])
		size++;
	new_envp = (char **)malloc(sizeof(char *) * (size + 2));
	while (++i < size)
		new_envp[i] = sh->envp[i];
	new_envp[size] = ft_strdup(arg);
	new_envp[size + 1] = NULL;
	free(sh->envp);
	sh->envp = new_envp;
}

void	export_cmd(t_bash *sh, char *arg)
{
	char	*key;
	int		env_index;

	key = get_key(arg);
	if (!key)
		return ;
	env_index = find_key(sh, key);
	if (env_index >= 0)
		unset_cmd(sh, key);
	if (is_valid_format(arg))
		add_env(sh, arg);
	free(key);
}

void	handle_export(t_bash *sh, char **args)
{
	int		i;

	i = 0;
	if (!args[0])
	{
		sh->last_exit_status = 127;
		return ;
	}
	while (args[i])
	{
		export_cmd(sh, args[i]);
		i++;
	}
	sh->last_exit_status = 127;
}

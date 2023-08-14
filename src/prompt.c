/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:44:42 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/14 14:51:35 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

static int	ft_random(void)
{
	static unsigned int	seed = 42;

	seed = seed * 1664525 + 1013904223;
	return (seed % 4);
}

static char	*select_color_prompt(char *pwd)
{
	int		random;
	char	*prefix;
	char	*full_prompt;

	random = ft_random();
	if (random == 0)
		prefix = "\033[0;32m[";
	else if (random == 1)
		prefix = "\033[0;36m[";
	else if (random == 2)
		prefix = "\033[0;34m[";
	else
		prefix = "\033[0;35m[";
	prefix = ft_strjoin(prefix, pwd);
	full_prompt = ft_strjoin(prefix, "] > \033[0m");
	free(prefix);
	return (full_prompt);
}

char	*prompt_content(t_bash *sh)
{
	int		i;
	char	*pwd;
	char	*tmp;

	i = -1;
	pwd = NULL;
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
	if (pwd == NULL)
		return ("minishell> ");
	tmp = select_color_prompt(pwd);
	free (pwd);
	pwd = tmp;
	return (pwd);
}

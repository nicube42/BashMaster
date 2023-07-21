/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:16:51 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/21 16:22:36 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

void	expander(t_bash *sh, char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	sh->lexed[sh->lexed_size + 1] = 0;
	while (sh->lexed[++i])
	{
		if (sh->lexed[i][0] == '$')
		{
			tmp = ft_substr(sh->lexed[i], 1, ft_strlen(sh->lexed[i]));
			j = -1;
			while (envp[++j])
			{
				if (!ft_strncmp(tmp, envp[j], ft_strlen(tmp))
					&& envp[j][ft_strlen(tmp)] == '=')
				{
					tmp = ft_substr(envp[j],
							ft_strlen(tmp) + 1, ft_strlen(envp[j]));
					sh->lexed[i] = ft_strdup(tmp);
					break ;
				}
			}
		}
	}
}

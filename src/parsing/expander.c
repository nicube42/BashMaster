/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:16:51 by ndiamant          #+#    #+#             */
/*   Updated: 2023/07/27 10:40:37 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	replace_substring(char **str, int start, int end, char *replacement)
{
	char	*new_str;
	char	*prefix;
	char	*suffix;

	prefix = ft_substr(*str, 0, start);
	suffix = ft_substr(*str, end, ft_strlen(*str) - end);
	new_str = ft_strjoin(ft_strjoin(prefix, replacement), suffix);
	free(prefix);
	free(suffix);
	free(*str);
	*str = new_str;
}

void	expander(t_bash *sh, char **envp)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*tmp;

	i = -1;
	j = -1;
	sh->lexed[sh->lexed_size] = 0;
	while (sh->lexed[++i])
	{
		k = -1;
		while (sh->lexed[i][++k])
		{
			if (sh->lexed[i][k] == '$' && sh->is_quote[i] == 0)
			{
				l = k;
				while (!ft_is_blank(sh->lexed[i][l]) && sh->lexed[i][l])
					l++;
				tmp = ft_substr(sh->lexed[i], k + 1, ft_strlen(sh->lexed[i]));
				j = -1;
				while (envp[++j])
				{
					if (!ft_strncmp(tmp, envp[j], ft_strlen(tmp))
						&& envp[j][ft_strlen(tmp)] == '=')
					{
						free (tmp);
						tmp = ft_substr(envp[j],
								ft_strlen(tmp) + 1, ft_strlen(envp[j]));
						replace_substring(&sh->lexed[i], k, l, tmp);
						free (tmp);
						break ;
					}
				}
			}
		}
	}
}

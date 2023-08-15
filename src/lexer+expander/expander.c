/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:16:51 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/15 17:25:53 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	replace_substring(char **str, t_exp *exp, t_bash *sh)
{
	char	*new_str;
	char	*prefix;
	char	*suffix;
	char	*temp_str;

	prefix = ft_substr(*str, 0, exp->k);
	if (!prefix)
		clean_exit("Malloc error", sh);
	suffix = ft_substr(*str, exp->l, ft_strlen(*str) - exp->l);
	if (!suffix)
		clean_exit("Malloc error", sh);
	temp_str = ft_strjoin(prefix, exp->tmp);
	if (!temp_str)
		clean_exit("Malloc error", sh);
	new_str = ft_strjoin(temp_str, suffix);
	if (!new_str)
		clean_exit("Malloc error", sh);
	free(prefix);
	free(suffix);
	free(temp_str);
	free(*str);
	*str = new_str;
}

void	expand_last_exit_status(t_bash *sh, t_exp *exp)
{
	char	*tmp;

	tmp = ft_itoa(sh->last_exit_status);
	if (!tmp)
		clean_exit("Malloc error", sh);
	exp->tmp = tmp;
	replace_substring(&sh->lexed[exp->i], exp, sh);
}

static void	expand_variable(t_bash *sh, t_exp *exp)
{
	if (sh->lexed[exp->i][exp->k] == '$' && sh->is_quote[exp->i] == 0)
	{
		if (sh->lexed[exp->i][exp->k + 1] == '?')
		{
			exp->l = exp->k + 1;
			expand_last_exit_status(sh, exp);
			return ;
		}
		exp->l = exp->k;
		while (!ft_is_blank(sh->lexed[exp->i][exp->l])
			&& sh->lexed[exp->i][exp->l])
			exp->l++;
		expander_2(sh, exp);
	}
}

void	expander(t_bash *sh, char **envp)
{
	int		j;
	t_exp	*exp;

	(void) envp;
	exp = malloc(sizeof(t_exp));
	if (!exp)
		clean_exit("Malloc error", sh);
	exp->i = -1;
	j = -1;
	sh->lexed[sh->lexed_size] = 0;
	while (sh->lexed[++exp->i])
	{
		exp->k = -1;
		while (sh->lexed[exp->i][++exp->k])
			expand_variable(sh, exp);
	}
	if (exp)
		free(exp);
}

int	get_substr_length(char *str, int start_idx)
{
	int	len;

	len = 0;
	while (str[start_idx + len] && str[start_idx + len] != '\'')
		len++;
	return (len);
}

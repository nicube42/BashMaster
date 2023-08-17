/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 01:16:51 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/17 14:20:06 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	replace_substring(char **str, t_exp *exp, t_bash *sh)
{
	char	*new_str;

	new_str = create_new_string(str, exp, sh);
	free(*str);
	*str = new_str;
	exp->k = ft_strlen(*str) - 1;
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
			exp->l = exp->k + 2;
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
		exp->m = -1;
		exp->k = -1;
		while (sh->lexed[exp->i][++exp->m])
		{
			exp->k = exp->m;
			expand_variable(sh, exp);
		}
	}
	if (exp)
		free(exp);
}

int	get_substr_length(char *str, int start_idx)
{
	int	len;

	len = 0;
	while (str[start_idx + len] && str[start_idx + len] != '\''
		&& str[start_idx + len] != ' ')
		len++;
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/31 21:56:52 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

//to delete at the end
void	ft_print_tokens(t_bash *sh)
{
	t_list	*list;
	int		i;
	int		j;

	i = 1;
	list = sh->first;
	while (list)
	{
		j = 0;
		printf("value number %d : %s\n", i, list->value);
		if (list->arguments != 0)
		{
			while (list->arguments[j])
			{
				printf("      arguments %d : %s\n", j + 1, list->arguments[j]);
				j++;
			}
		}
		printf("id = %d\n", list->id);
		printf("fdin = %d\n", list->fd_in);
		printf("fdout = %d\n", list->fd_out);
		i++;
		printf("\n");
		list = list->next;
	}
}

char	*prompt_content(t_bash *sh)
{
	int		i;
	char	*pwd;

	i = -1;
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
	pwd = ft_strjoin(ft_strjoin("\033[0;32m[", pwd), "] > \033[0m");
	return (pwd);
}

void	repete_prompt(t_bash *sh, char **envp)
{
	while (1)
	{
		init_struct(sh, envp);
		sh->input = readline(prompt_content(sh));
		if (sh->input[0] == '\0')
			continue ;
		add_history(sh->input);
		count_quote(sh->input, sh);
		lexer_size(sh->input, sh);
		ft_memset(sh->is_quote, 0, sizeof(int) * sh->lexed_size);
		lexer(sh->input, sh);
		expander(sh, envp);
		parser(sh);
		set_last_of_list(sh);
		if (check_syntax(sh))
			execution(sh);
		destroy_tokens(sh);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_bash	sh;
	char	*input;

	(void) ac;
	(void) av;
	using_history();
	write(1, "\n", 1);
	repete_prompt(&sh, envp);
	return (0);
}

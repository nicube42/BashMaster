/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/28 11:10:44 by ndiamant         ###   ########.fr       */
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
		i++;
		printf("\n");
		list = list->next;
	}
}

void	repete_prompt(t_bash *sh, char **envp)
{
	while (1)
	{
		init_struct(sh, envp);
		sh->input = readline(GREEN "[ 🎓 BashMaster 🎓 ] > " RESET);
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
			execute(sh);
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

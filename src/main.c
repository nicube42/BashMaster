/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/28 10:13:37 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

int	main(int ac, char *av[], char *envp[])
{
	t_bash	sh;
	char	*input;

	(void) ac;
	(void) av;
	using_history();
	write(1, "\n", 1);
	while (1)
	{
		init_struct(&sh, envp);
		sh.input = readline(GREEN "[ 🎓 BashMaster 🎓 ] > " RESET);
		if (sh.input[0] == '\0')
			continue ;
		add_history(sh.input);
		count_quote(sh.input, &sh);
		lexer_size(sh.input, &sh);
		ft_memset(sh.is_quote, 0, sizeof(int) * sh.lexed_size);
		lexer(sh.input, &sh);
		expander(&sh, envp);
		parser(&sh);
		set_last_of_list(&sh);
		if (check_syntax(&sh))
			execute(&sh);
		destroy_tokens(&sh);
	}
	return (0);
}

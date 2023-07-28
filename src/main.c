/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/28 10:02:50 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

char	**ft_parsing_execve(char **envp, t_bash *sh)
{
	int		i;
	char	*full_path;
	char	**splitted_path;
	char	*tmp;

	i = 0;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			full_path = envp[i] + 5;
	}
	splitted_path = ft_split(full_path, ':');
	if (!splitted_path)
		clean_exit("Malloc error", sh);
	i = -1;
	while (splitted_path[++i])
	{
		tmp = ft_strjoin(splitted_path[i], "/");
		if (!tmp)
			clean_exit("Malloc error", sh);
		if (splitted_path[i])
			free(splitted_path[i]);
		splitted_path[i] = tmp;
	}
	return (splitted_path);
}

void	count_quote(char *input, t_bash *sh)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_is_quote(input[i]) == 1)
			sh->dquote_count ++;
		if (ft_is_quote(input[i]) == 2)
			sh->quote_count++;
		i++;
	}
}

void	set_last_of_list(t_bash *sh)
{
	t_list	*list;

	list = sh->first;
	while (list)
		list = list->next;
	sh->last = list;
}

void	init_struct(t_bash *sh, char **envp)
{
	sh->lexed = NULL;
	sh->lexed_size = 0;
	sh->lexed_current = 0;
	sh->dquote_count = 0;
	sh->quote_count = 0;
	sh->envp = envp;
	sh->splitted_path = ft_parsing_execve(envp, sh);
	sh->input = 0;
}

void	clean_exit(char *msg, t_bash *sh)
{
	ft_printf("%s\n", msg);
	destroy_tokens(sh);
	exit(1);
}

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
		if (!check_syntax(&sh))
			execute(&sh);
		destroy_tokens(&sh);
	}
	return (0);
}

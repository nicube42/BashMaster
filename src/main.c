/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/08/11 11:50:44 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

int g_quit_heredoc = 0;

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

int	ft_random(void)
{
	static unsigned int	seed = 42;

	seed = seed * 1664525 + 1013904223;
	return (seed % 4);
}

char	*select_color_prompt(char *pwd)
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
	tmp = select_color_prompt(pwd);
	free (pwd);
	pwd = tmp;
	return (pwd);
}

void	repete_prompt(t_bash *sh)
{
	char	*pwd;

	sh->last_exit_status = -1;
	int i = -1;
	while (++i < 1)
	{
		setup_signals();
		init_struct(sh, sh->envp);
		pwd = prompt_content(sh);
		sh->input = readline(pwd);
		free (pwd);
		if (sh->input == NULL)
		{
			if (g_quit_heredoc)
				write(1, "\n", 1);
			else
				break ;
		}
		if (sh->input[0] == '\0')
			continue ;
		add_history(sh->input);
		count_quote(sh->input, sh);
		lexer_size(sh->input, sh);
		ft_memset(sh->is_quote, 0, sizeof(int) * sh->lexed_size);
		lexer(sh->input, sh);
		expander(sh, sh->envp);
		parser(sh);
		set_last_of_list(sh);
		if (sh->lexed_size > 0 && check_syntax(sh))
			execution(sh);
		destroy_tokens(sh);
	}
	free_envp(sh);
}

int	main(int ac, char **av, char *envp[])
{
	t_bash	sh;
	char	*input;
	int		i;

	(void) av;
	i = 0;
	while (envp[i])
		i++;
	sh.envp = malloc (sizeof(char *) * i + 1);
	i = -1;
	while (envp[++i])
		sh.envp[i] = ft_strdup(envp[i]);
	disable_ctrl_c_echo();
	using_history();
	write(1, "\n", 1);
	if (ac == 1)
		repete_prompt(&sh);
	else
		printf("No args accepted in minishell.\n");
	return (0);
}

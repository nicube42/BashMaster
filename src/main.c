/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/08/15 18:20:49 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

int	g_quit_heredoc = 0;

static void	sigint_main_handler(int sig)
{
	(void) sig;
	if (g_quit_heredoc == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_input(t_bash *sh)
{
	if (sh->input[0] == '\0')
		return ;
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

static void	repete_prompt(t_bash *sh)
{
	char	*pwd;

	sh->last_exit_status = -1;
	while (1)
	{
		signal(SIGINT, sigint_main_handler);
		signal(SIGQUIT, SIG_IGN);
		init_struct(sh, sh->envp);
		pwd = prompt_content(sh);
		sh->input = readline(pwd);
		if (ft_strncmp(pwd, "minishell> ", 13))
			free(pwd);
		if (sh->input == NULL)
		{
			if (g_quit_heredoc)
				write(1, "\n", 1);
			else
				break ;
		}
		handle_input(sh);
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_bash	sh;
	int		i;

	(void) av;
	i = 0;
	while (envp[i])
		i++;
	sh.envp = malloc (sizeof(char *) * (i + 1));
	if (!sh.envp)
		return (1);
	sh.envp[i] = 0;
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
	free_envp(&sh);
	return (0);
}

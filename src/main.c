/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/20 01:44:07 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

char	**ft_parsing_execve(char **envp)
{
	int		i;
	char	*full_path;
	char	**splitted_path;

	i = 0;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			full_path = envp[i] + 5;
	}
	splitted_path = ft_split(full_path, ':');
	i = -1;
	while (splitted_path[++i])
		splitted_path[i] = ft_strjoin(splitted_path[i], "/");
	return (splitted_path);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_bash	sh;
	int		i;

	i = -1;
	sh.lexed_size = 0;
	sh.lexed_current = 0;
	line = "<redir   $test   ls    -a|base64|$USER>redir |ls -la <<    redir";
	lexer_size(line, &sh);
	sh.lexed = malloc(sizeof(char *) * sh.lexed_size + 1);
	lexer(line, &sh);
	expander(&sh, envp);
	while (sh.lexed[++i])
		printf("%s\n", sh.lexed[i]);
}

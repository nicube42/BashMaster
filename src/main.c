/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/20 00:34:13 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

int	main(void)
{
	char	*line;
	t_bash	sh;
	int		i;

	i = -1;
	sh.lexed_size = 0;
	sh.lexed_current = 0;
	line = "<redir         ls     -a|base64|$USR>redir |ls -la <<    redir";
	lexer_size(line, &sh);
	sh.lexed = malloc(sizeof(char *) * sh.lexed_size + 1);
	lexer(line, &sh);
	while (sh.lexed[++i])
		printf("%s\n", sh.lexed[i]);
}

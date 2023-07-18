/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:48:01 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/18 19:23:48 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bashmaster.h"

int	main(void)
{
	char	*line;

	line = "<redir ls -a | base64| $USR>redir<<redir";
	lexer(line);
}

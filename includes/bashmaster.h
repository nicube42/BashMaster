/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashmaster.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:01:49 by ivautrav          #+#    #+#             */
/*   Updated: 2023/07/18 18:39:21 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASHMASTER_H
# define BASHMASTER_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

typedef struct s_command
{

}	t_command;

typedef struct s_bash
{

}	t_bash;

char	**lexer(char *input);

#endif
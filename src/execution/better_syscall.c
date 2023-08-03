/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_syscall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:44:50 by ndiamant          #+#    #+#             */
/*   Updated: 2023/08/03 19:26:45 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bashmaster.h"

void	better_dup2(int to_change, int new)
{
	if (dup2(to_change, new) == -1)
	{
		perror("Error duplicating file descriptor");
		exit(EXIT_FAILURE);
	}
}

void	better_close(int to_close)
{
	if (close(to_close))
	{
		perror("Error closing file descriptor");
		exit(EXIT_FAILURE);
	}
}

void	better_write(int fd, char *value, size_t size)
{
	if (write(fd, value, size) == -1)
	{
		perror("Error during write");
		exit(EXIT_FAILURE);
	}
}

void	better_unlink(char *name)
{
	if (unlink(name) == -1)
	{
		perror("Error during unlink");
		exit(EXIT_FAILURE);
	}
}

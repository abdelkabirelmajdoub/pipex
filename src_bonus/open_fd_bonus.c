/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:29:48 by ael-majd          #+#    #+#             */
/*   Updated: 2025/01/30 15:01:13 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	file_open(char *file, int std)
{
	int	fd;

	if (std == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror("infile error");
			exit(1);
		}
	}
	if (std == 1)
	{
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
		{
			perror("outfile error");
			exit(1);
		}
	}
	return (fd);
}

int	fd_here_doc(char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("outfile error");
		exit(1);
	}
	return (fd);
}

void	change_fd(int pfd, int place)
{
	if (place == 1)
	{
		if (dup2(pfd, STDOUT_FILENO) == -1)
		{
			perror("dup2 error");
			exit(1);
		}
	}
	if (place == 0)
	{
		if (dup2(pfd, STDIN_FILENO) == -1)
		{
			perror("dup2 error");
			exit(1);
		}
	}
}

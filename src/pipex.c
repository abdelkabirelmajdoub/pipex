/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:41:25 by ael-majd          #+#    #+#             */
/*   Updated: 2025/01/22 13:56:38 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**full_cmd;
	char	*path;

	full_cmd = ft_split(cmd, ' ');
	path = get_path(full_cmd[0], env);
	if (execve(path, full_cmd, env) == -1)
	{
		perror("exec error");
		free_paths(full_cmd);
		exit(1);
	}
}

void	child_process(char **av, int *pipefd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1 )
	{
		perror("infile error");
		close(pipefd[1]);
		close(pipefd[0]);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 in fd error");
		close(fd);
		exit(1);
	}
	close(fd);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 in pipefd error");
		exit(1);
	}
	close(pipefd[1]);
	exec_cmd(av[2], env);
}

void	parent_process(char **av, int *pipefd, char **env)
{
	int	fd;

	fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("outfile error");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 in fd error");
		close(fd);
		exit(1);
	}
	close(fd);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 in pipefd error");
		exit(1);
	}
	close(pipefd[0]);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int	pipefd[2];
	int	pid;

	if (ac != 5)
	{
		ft_putstr_fd("Bad arguments:\n./pipex infile cmd cmd outfile\n", 2);
		exit(1);
	}
	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		child_process(av, pipefd, env);
	else if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	parent_process(av, pipefd, env);
	return (0);
}

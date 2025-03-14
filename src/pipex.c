/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:41:25 by ael-majd          #+#    #+#             */
/*   Updated: 2025/02/20 12:30:01 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**full_cmd;
	char	*path;

	full_cmd = parse_args(cmd);
	path = get_path(full_cmd[0], env);
	if (execve(path, full_cmd, env) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(full_cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free_paths(full_cmd);
		exit(1);
	}
}

void	child_process(char **av, int *pipefd, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
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
	int	pid1;
	int	pid2;

	if (!env || !*env)
		return (1);
	if (ac != 5)
		error(5);
	if (pipe(pipefd) == -1)
		error(0);
	pid1 = fork();
	if (pid1 == 0)
		child_process(av, pipefd, env);
	else if (pid1 == -1)
		error(3);
	pid2 = fork();
	if (pid2 == 0)
		parent_process(av, pipefd, env);
	else if (pid2 == -1)
		error(3);
	close(pipefd[1]);
	close(pipefd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

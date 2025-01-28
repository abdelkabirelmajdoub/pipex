/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:30:38 by ael-majd          #+#    #+#             */
/*   Updated: 2025/01/28 13:48:01 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**full_cmd;
	char	*path;

	full_cmd = ft_split(cmd, ' ');
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

void	child_process(char *cmd, char **env)
{
	pid_t	pid;
	int		fdpipe[2];

	if (pipe(fdpipe) == -1)
		error(0);
	pid = fork();
	if (pid == -1)
		error(3);
	if (pid == 0)
	{
		close(fdpipe[0]);
		dup2(fdpipe[1], STDOUT_FILENO);
		close(fdpipe[1]);
		exec_cmd(cmd, env);
	}
	else
	{
		close(fdpipe[1]);
		dup2(fdpipe[0], STDIN_FILENO);
		close(fdpipe[0]);
	}
}

void	run_here_doc(char *limitter, int *fdpipe)
{
	char	*line;

	close(fdpipe[0]);
	while (1)
	{
		ft_putstr_fd("here_doc_running>", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, limitter, ft_strlen(limitter)) == 0 
			&& ft_strlen(line) == ft_strlen(limitter) + 1)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, fdpipe[1]);
		free(line);
	}
}

void	here_doc(char *limitter)
{
	int		fdpipe[2];
	pid_t	pid;

	if (pipe(fdpipe) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		error(3);
	if (pid == -1)
		exit(1);
	if (pid == 0)
		run_here_doc(limitter, fdpipe);
	else
	{
		waitpid(pid, NULL, 0);
		close(fdpipe[1]);
		dup2(fdpipe[0], STDIN_FILENO);
		close(fdpipe[0]);
	}
}

int	main(int ac, char **av, char **env)
{
	int	in;
	int	out;
	int	i;

	check_error(ac, 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		check_error(ac, 2);
		i = 3;
		out = fd_here_doc(av[ac - 1]);
		here_doc(av[2]);
	}
	else 
	{
		i = 2;
		in = file_open(av[1], 0);
		dup2(in, STDIN_FILENO);
		close(in);
		out = file_open(av[ac - 1], 1);
	}
	while (i < ac - 2)
		child_process(av[i++], env);
	dup2(out, STDOUT_FILENO);
	close(out);
	exec_cmd(av[ac - 2], env);
}

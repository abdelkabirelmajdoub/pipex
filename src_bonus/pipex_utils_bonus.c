/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:16:15 by ael-majd          #+#    #+#             */
/*   Updated: 2025/01/25 16:26:41 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j + 1);
		if (ft_strncmp(sub, name, 4) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

void	free_paths(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	*get_path(char *cmd, char **env)
{
	char	*path_part;
	char	*exec;
	char	**secure_paths;
	int		i;

	secure_paths = ft_split(my_getenv("PATH", env), ':');
	i = 0;
	while (secure_paths[i])
	{
		path_part = ft_strjoin(secure_paths[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_paths(secure_paths);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_paths(secure_paths);
	return (cmd);
}

void	error(int n)
{
	if (n == 1)
	{
		ft_putstr_fd("Bad arguments:\n", 2);
		ft_putstr_fd("./pipex infile <cmd1> ... <cmdn> outfile\n", 2);
	}
	else if (n == 2)
	{
		ft_putstr_fd("Bad arguments:\n", 2);
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
	}
	else if (n == 3)
		ft_putstr_fd("fork error", 2);
	else 
		perror("Pipe Error");
	exit(EXIT_FAILURE);
}

void	check_error(int ac, int n)
{
	if (ac < 5 && n == 1)
		error(n);
	if (ac < 6 && n == 2)
		error(n);
}

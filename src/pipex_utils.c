/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:16:15 by ael-majd          #+#    #+#             */
/*   Updated: 2025/02/01 13:57:53 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (n == 3)
		ft_putstr_fd("fork error", 2);
	else if (n == 5)
	{
		ft_putstr_fd("Bad arguments:\n./pipex infile cmd cmd outfile\n", 2);
		exit(1);
	}
	else 
		perror("Pipe Error");
	exit(EXIT_FAILURE);
}

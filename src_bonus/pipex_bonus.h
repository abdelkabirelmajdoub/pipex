/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:28:07 by ael-majd          #+#    #+#             */
/*   Updated: 2025/02/20 13:38:18 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "GNL/get_next_line_bonus.h"

char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
char	**parse_args(char *cmd);
int		file_open(char *file, int std);
int		fd_here_doc(char *file);
int		file_open(char *file, int std);
void	check_error(int ac, int n);
void	error(int n);
void	free_paths(char **s);
void	change_fd(int pfd, int place);
void	last_cmd(char **av, char **env, int ac, int out);
void	exec_cmd(char *cmd, char **env);
void	wait_mychildren(void);
void	setup(int *i, int *in, char *filename);
#endif
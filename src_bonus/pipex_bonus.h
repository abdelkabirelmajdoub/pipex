/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:28:07 by ael-majd          #+#    #+#             */
/*   Updated: 2025/02/01 13:47:36 by ael-majd         ###   ########.fr       */
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
void	free_paths(char **s);
void	error(int n);
void	check_error(int ac, int n);
int		file_open(char *file, int std);
int		fd_here_doc(char *file);
void	change_fd(int pfd, int place);
int		file_open(char *file, int std);
char	**parse_args(char *cmd);
#endif
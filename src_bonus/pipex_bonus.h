/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:28:07 by ael-majd          #+#    #+#             */
/*   Updated: 2025/01/23 12:28:51 by ael-majd         ###   ########.fr       */
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
int		open_files(char *file, int in_out);
void	free_paths(char **s);
void	error(int n);
void	check_error(int ac);
#endif
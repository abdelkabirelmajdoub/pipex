/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:28:07 by ael-majd          #+#    #+#             */
/*   Updated: 2025/02/01 13:47:17 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	free_paths(char **s);
void	error(int n);
char	**parse_args(char *cmd);
#endif
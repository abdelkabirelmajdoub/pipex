/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-majd <ael-majd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:09:53 by ael-majd          #+#    #+#             */
/*   Updated: 2025/02/01 13:57:34 by ael-majd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	skip_spaces(char *s, int *i)
{
	while (s[*i] == ' ')
		(*i)++;
}

char	*in_quote(char *cmd, int *i, int *start)
{
	(*i)++;
	*start = *i;
	while (cmd[*i] && cmd[*i] != '\'')
		(*i)++;
	if (cmd[*i] == '\'')
		return (ft_substr(cmd, *start, *i++ - *start));
	return (NULL);
}

char	*out_quote(char *cmd, int *a, int *start)
{
	while (cmd[*a] && cmd[*a] != ' ')
		(*a)++;
	return (ft_substr(cmd, *start, *a - *start));
}

char	**parse_args(char *cmd)
{
	char	**args;
	int		i;
	int		count;
	int		start;

	args = malloc(sizeof(char *) * 42);
	if (!args)
		return (NULL);
	i = 0;
	count = 0;
	while (cmd[i])
	{
		skip_spaces(cmd, &i);
		if (!cmd[i])
			break ;
		start = i;
		if (cmd[i] == '\'')
			args[count] = in_quote(cmd, &i, &start);
		else
			args[count] = out_quote(cmd, &i, &start);
		count++;
	}
	args[count] = NULL;
	return (args);
}

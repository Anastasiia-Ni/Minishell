/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:39:21 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/02 14:29:11 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(char **env)
{
	char	**new;
	int		i;

	i = 0;
	while (env[i])
		++i;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		++i;
	}
	new[i] = 0;
	return (new);
}

char	**sort_env(char **env)
{
	char	**new;
	char	*tmp;
	int		done;
	int		i;

	new = cpy_env(env);
	done = 0;
	while (!done)
	{
		done = 1;
		i = 0;
		while (new[i + 1])
		{
			if (ft_strcmp(new[i], new[i + 1]) > 0)
			{
				tmp = new[i];
				new[i] = new[i + 1];
				new[i + 1] = tmp;
				done = 0;
			}
			++i;
		}
	}
	return (new);
}

int	check_quotes(char *line)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quotes == 0)
			quotes = 1;
		else if (line[i] == '\"' && quotes == 1)
			quotes = 0;
		else if (line[i] == '\'' && quotes == 0)
			quotes = 2;
		else if (line[i] == '\'' && quotes == 2)
			quotes = 0;
		if (line[i] == '$' && (quotes == 1 || quotes == 0))
			line[i] = 1;
		++i;
	}
	return (quotes);
}

char	*find_not_env(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != 1)
		i++;
	if (i < 1)
		return (NULL);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != 1)
	{
		new[i] = str[i];
		++i;
	}
	new[i] = '\0';
	return (new);
}

void	expand(char **cmd, t_prog *prog)
{
	char	*tmp;
	char	*expan;

	tmp = find_not_env(*cmd);
	expan = find_env(*cmd, prog);
	free(*cmd);
	*cmd = ft_strjoin(tmp, expan, 0);
	if (tmp)
		free(tmp);
	if (expan)
		free(expan);
}

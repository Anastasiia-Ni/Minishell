/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:09:18 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/01 13:52:40 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig)
{
	(void)sig;
	if (g_pid == 0)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(2, "\n", 1);
}

void	sig_quit(int sig)
{
	(void)sig;
	if (g_pid != 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
}

void	interrupt_delim(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(0);
}

int	next_pipe(t_prog *prog, int i)
{
	while (prog->token[i])
	{
		if (prog->type[i] == PIPE)
			return (i);
		++i;
	}
	return (i - 1);
}

int	check_hyphen(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] && line[i + 1] == '<'
		&& line[i + 2] && line[i + 2] == '-')
		return (1);
	return (0);
}

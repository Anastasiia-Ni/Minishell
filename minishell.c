/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:07:13 by kabusitt          #+#    #+#             */
/*   Updated: 2022/02/18 05:08:57 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pid;

void	close_fds(t_prog *prog)
{
	if (prog->fdin > 0)
		close(prog->fdin);
	if (prog->fdout > 0)
		close(prog->fdout);
}

int	next_op(t_prog *prog, int i)
{
	while (prog->token[i])
	{
		if (check_type(prog, i, "RAIDP"))
			return (i);
		++i;
	}
	return (i - 1);
}

void	run_prog(t_prog *prog)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (prog->token[i])
	{
		while (check_type(prog, next_op(prog, z), "RAID"))
		{
			z = next_op(prog, z) + 1;
			redir(prog, z);
		}
		if ((i == 0 || (i > 0 && prog->type[i - 1] == PIPE)) && !prog->err)
			parse_exec(prog, i);
		i = next_pipe(prog, i) + 1;
		z = i;
		prog->pipnum++;
	}
}

void	shell(t_prog *prog)
{
	if (pipe_size(prog) > 0)
	{
		prog->exec = 0;
		pipe_init(prog);
	}
	prog->err = 0;
	prog->pipnum = 0;
	prog->delim = 0;
	prog->redinput = 0;
	prog->redoutput = 0;
	run_prog(prog);
	reset_fd(prog);
	close_fds(prog);
	if (pipe_size(prog) > 0)
		free(prog->pipfd);
	free_split(prog->token);
	free(prog->type);
}

int	main(int argc, char **argv, char **envp)
{
	t_prog	prog;
	int		ret;

	prog.in = dup(0);
	prog.out = dup(1);
	(void)argc;
	(void)argv;
	prog.env = envp;
	prog.ret = 0;
	prog.sort_env = sort_env(envp);
	//printf("\033[?1049h\033[H");
	while (1)
	{
		prog.fdin = -1;
		prog.fdout = -1;
		g_pid = 0;
		prog.exec = 1;
		ret = parseline(&prog);
		if (ret == 1)
			break ;
		if (ret == 0 && check_token(&prog))
			shell(&prog);
	}
	free_split(prog.sort_env);
	return (0);
}

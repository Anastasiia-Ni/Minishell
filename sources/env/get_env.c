/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:52:44 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/17 16:40:22 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(char *env, t_prog *prog)
{
	char	*var;
	char	**split;
	int		i;

	i = 0;
	if (env[0] == '=' && env[1] == '\0')
		return (ft_strdup("$"));
	if (!ft_strcmp(env, "?="))
		return (ft_itoa(prog->ret));
	else
	{
		while (prog->env[i]
			&& ft_strncmp(prog->env[i], env, ft_strlen(env) - 1) != 0)
			++i;
		if (!prog->env[i])
			return (NULL);
		split = ft_split(prog->env[i], '=');
		var = ft_strdup(split[1]);
		free_split(split);
		return (var);
	}
}

void	builtin_chk(t_prog *prog, char **cmd)
{
	if (pipe_size(prog) > 0 && !prog->redoutput)
	{
		g_pid.pid[g_pid.index] = fork();
		if (g_pid.pid[g_pid.index] == 0)
		{
			builtin_pipe(prog);
			builtin_exec(prog, cmd);
			close_pipes(prog);
			close_std(prog, -1);
			exit(0);
		}
		close_piptmp(prog);
		g_pid.index++;
	}
	else
	{
		builtin_exec(prog, cmd);
		if (pipe_size(prog) > 0)
			close_piptmp(prog);
		g_pid.status[g_pid.index++] = -1;
	}
}

void	print_error_c(t_prog *prog, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	prog->ret = 127;
}

void	dup_delim(int fd)
{
	close(fd);
	fd = open(".tmpdelim", O_RDONLY);
	unlink(".tmpdelim");
	dup2(fd, 0);
	close(fd);
}

void	loop_delim(t_prog *prog, char *delim, int fd, int z)
{
	char	*line;

	signal(SIGINT, interrupt_delim);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			readline_fix(prog, 1);
			break ;
		}
		if (prog->type[z - 1] == DELIM_TAB)
			line = remove_tabs(line);
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$'))
			expand(&line, prog);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close_std(prog, fd);
	exit(0);
}

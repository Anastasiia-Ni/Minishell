/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <anifanto@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:33:05 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/06 15:53:10 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_full_exit(t_prog *prog)
{
	free_split(prog->env);
	free_split(prog->token);
	free(prog->type);
	exit(prog->ret);
}

static void	ft_print_error_exit(t_prog *prog)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(prog->token[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	prog->ret = 255;
}

static int	ft_check_digit(char *str)
{
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_prog *prog)
{
	if (prog->token[1])
	{
		if (!ft_check_digit(prog->token[1]))
			ft_print_error_exit(prog);
		else
		{
			prog->ret = ft_atoi(prog->token[1]) % 256;
			if (prog->token[2])
			{
				ft_putendl_fd("exit", 2);
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				prog->ret = 1;
				return ;
			}
			else
				ft_putendl_fd("exit", 1);
		}
	}
	else
		ft_putendl_fd("exit", 1);
	ft_full_exit(prog);
}

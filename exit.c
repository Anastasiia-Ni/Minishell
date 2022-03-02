#include "minishell.h"

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
			prog->ret = 255;
		else
		{
			prog->ret = ft_atoi(prog->token[1]) % 256;
			if (prog->token[2])
			{
				ft_putendl_fd("bash: exit: too many arguments", 2);
				prog->ret = 1;
				return ;
			}
		}
	}
	printf("exit\n");
	exit(prog->ret);
}

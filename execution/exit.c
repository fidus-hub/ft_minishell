/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:33 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 00:49:34 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <ctype.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	half_ft_exit(char **args)
{
	int	j;

	j = 0;
	while (args[1][j])
	{
		if (!(ft_isdigit(args[1][j])))
		{
			write(2, "exit\n", 6);
			write(2, "minishell: exit:", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, "numeric argument required\n", 26);
			exit(255);
		}
		j++;
	}
	if (args[2] == NULL)
	{
		__get_var(SETEXIT, atoi(args[1]));
		write(2, "exit\n", 6);
		exit(atoi(args[1]));
	}
}

int	checknumber(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(t_cmds *cmd)
{
	char	**args;

	args = cmd->args;
	if (!args[1])
	{
		write(2, "exit\n", 6);
		exit(__get_var(GETEXIT, 0));
	}
	if (args[2] != NULL)
	{
		if (checknumber(args[1]))
		{
			write(2, "exit\n", 6);
			write(2, "minishell: exit: too many arguments\n", 37);
			__get_var(SETEXIT, 1);
			return (1);
		}
		write(2, "minishell: numeric argument required\n", 37);
		exit(255);
	}
	half_ft_exit(args);
	return (0);
}

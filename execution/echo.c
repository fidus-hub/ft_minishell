#include "execution.h"

void	ft_check_newline(t_cmds *cmd, int *t, int *n)
{
	int	k;

	k = 0;
	while (cmd->args[*t])
	{
		k = 0;
		if (cmd->args[*t][k] != '-' || (cmd->args[*t][k] == '-'
			&& cmd->args[*t][k + 1] != 'n'))
			break ;
		else
		{
			k++;
			while (cmd->args[*t][k] == 'n')
				k++;
			if (cmd->args[*t][k] == '\0')
				*n = 1;
			else
				break ;
		}
		(*t)++;
	}
}

void	n_zero(t_cmds *cmd, int t)
{
	while (cmd->args[t])
	{
		write(1, cmd->args[t], ft_strlen(cmd->args[t]));
		if (cmd->args[t + 1])
			write(1, " ", 1);
		t++;
	}
	write(1, "\n", 1);
}

void	echo(t_cmds *cmd)
{
	int	n;
	int	t;

	n = 0;
	t = 1;
	if (cmd->args[1])
	{
		ft_check_newline(cmd, &t, &n);
		if (n == 0)
			n_zero(cmd, t);
		else if (n == 1)
		{
			while (cmd->args[t])
			{
				write(1, cmd->args[t], ft_strlen(cmd->args[t]));
				if (cmd->args[t + 1])
					write(1, " ", 1);
				t++;
			}
		}
	}
	else
		write(1, "\n", 1);
	__get_var(SETEXIT, 0);
}

#include	"execution.h"
#include <ctype.h>

int	ft_exit(t_headers *headers)
{
	int		j;
	char	**args;

	args = headers->cmd_h->args;
	if (!args[1])
	{
		printf("exit\n");
		exit(__get_var(GETEXIT, 0));
	}
	if (args[2] != NULL)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		__get_var(SETEXIT, 1);
		return (1);
	}
	j = 0;
	while (args[1][j])
	{
		if (!(isdigit(args[1][j])))
		{
			printf("exit\n");
			printf("%s %s: %s \n", "minishell: exit:", args[1],
				"numeric argument required");
			exit(255);
		}
		j++;
	}
	if (args[2] == NULL)
	{
		__get_var(SETEXIT, atoi(args[1]));
		printf("exit\n");
		exit(__get_var(GETEXIT, 0));
	}
	return (0);
}

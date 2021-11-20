#include	"execution.h"

void	cd(t_cmds *cmd)
{
	int		i;
	char	*str;

	i = 0;
	if (cmd->args[1] == NULL)
	{
		str = getenv("HOME");
		if (str == 0)
			printf("minishell: cd: HOME not set\n");
		else
			i = chdir(str);
	}
	else if (cmd->args[1])
		i = chdir(cmd->args[1]);
	if (i != 0)
	{
		printf("cd: %s: No such file or directory\n", cmd->args[1]);
		__get_var(SETEXIT, 1);
	}
	else
		__get_var(SETEXIT, 0);
}
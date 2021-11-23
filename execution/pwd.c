#include	"execution.h"

void	pwd(t_cmds *cmd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", cwd);
	__get_var(SETEXIT, 0);
}

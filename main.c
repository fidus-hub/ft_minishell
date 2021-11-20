#include <stdio.h>

typedef enum e_norm
{
    GETEXIT,
    SETEXIT,
    GETPID,
    SETPID
}t_norm;

int		__get_var(t_norm op, int value)
{
	static int		exit_status = 0;
	static int		pids = 0;

	if (op == GETEXIT)
		return(exit_status);
	if (op == SETEXIT)
		exit_status = value;
	if (op == SETPID)
		pids = value;
	if (op == GETPID)
		return (pids);
	return (0);
}

int main()
{
   __get_var(SETEXIT, 66);
   __get_var(SETEXIT, 99);
    printf("%d\n", __get_var(GETEXIT, 0));
    return (-1);
}

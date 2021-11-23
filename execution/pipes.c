#include "execution.h"

void	ft_pipe(t_cmds *cmd, t_exec *exec)
{
	if (exec->in != 0)
	{
		dup2(exec->in, 0);
		close(exec->in);
	}
	if (exec->fd[1] != 1)
	{
		dup2(exec->fd[1], 1);
		close(exec->fd[1]);
	}
	close(exec->fd[0]);
}

void	ft_pipe_last(t_cmds *cmd, t_exec *exec)
{
	if (exec->in != 0)
	{
		dup2(exec->in, 0);
		close(exec->in);
	}
	if (exec->fd[1] > 2)
		close(exec->fd[1]);
}

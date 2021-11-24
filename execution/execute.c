/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:27 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 00:52:08 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_perror(char *c, char *s)
{
	write(2, "minishell: ", 12);
	write(2, c, ft_strlen(c));
	write(2, s, ft_strlen(s));
}

void	fill_env(t_exec *exec, t_headers *header)
{
	int		i;
	t_env	*env;

	i = 0;
	env = header->env_h;
	while (env)
	{
		if (env->val != NULL)
			i++;
		env = env->suivant;
	}
	exec->env = malloc(sizeof(char *) * (i + 1));
	env = header->env_h;
	i = 0;
	while (env)
	{
		if (env->val != NULL)
		{
			exec->env[i] = ft_strjoin(env->var, "=");
			exec->env[i] = ft_strjoin_free(exec->env[i], env->val);
			i++;
		}
		env = env->suivant;
	}
	exec->env[i] = 0;
}

void	half_exec_init(t_exec *exec, t_cmds **cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		i++;
		(*cmd)->path = NULL;
		*cmd = (*cmd)->next;
	}
	exec->path = NULL;
	exec->pid = malloc(sizeof(int) * (i));
	exec->nb_cmd = i;
	i = 0;
	exec->i = 0;
	exec->in = 0;
	exec->fd = malloc(sizeof(int) * 2);
}

void	exec_init(t_headers *header, t_exec *exec)
{
	t_env		*env;
	t_cmds		*cmd;
	int			i;

	i = 0;
	cmd = header->cmd_h;
	half_exec_init(exec, &cmd);
	env = header->env_h;
	while (env)
	{
		if (ft_strcmp(env->var, "PATH") == 0)
		{
			exec->path = ft_split(env->val, ':');
			break ;
		}
		env = env->suivant;
	}
	while (env && exec->path[i])
	{
		exec->path[i] = ft_strjoin_free(exec->path[i], "/");
		i++;
	}
	fill_env(exec, header);
}

void	exec_free(t_exec *exec)
{
	if (exec->path)
		ft_free(exec->path);
	free(exec->pid);
	ft_free(exec->env);
	free (exec->fd);
	free (exec);
}

void	join_path(t_exec *exec, t_cmds **cmd)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	while (exec->path && exec->path[i])
	{
		str = ft_strjoin(exec->path[i], (*cmd)->args[0]);
		fd = open(str, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			(*cmd)->path = ft_strjoin(exec->path[i], (*cmd)->args[0]);
			free(str);
			break ;
		}
		free(str);
		i++;
	}	
}

void	replace_arg(t_headers *header, t_exec *exec)
{
	t_cmds	*cmd;

	cmd = header->cmd_h;
	while (cmd)
	{
		join_path(exec, &cmd);
		if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
			cmd->path = ft_strdup(cmd->args[0]);
		cmd = cmd->next;
	}
}

void	ft_more_cmd(t_cmds *cmd, t_exec *exec)
{
	struct stat	buff;

	signal(SIGQUIT, SIG_DFL);
	if (cmd->path == NULL)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", ft_strlen(": command not found\n"));
	}
	else
	{
		if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
		{
			stat(cmd->args[0], &buff);
			if (buff.st_mode & S_IFDIR)
			{
				ft_perror(cmd->args[0], "is a directory\n");
				exit(126);
			}
		}
		execve(cmd->path, cmd->args, exec->env);
	}
	if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
		ft_perror(cmd->args[0], ": No such file or directory\n");
	exit(127);
}

void	print_error(t_cmds *cmd, char *s, int i)
{
	write(2, "minishell: ", 12);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, s, ft_strlen(s));
	if (i)
		exit (i);
}

void	child_proccess(t_cmds *cmd, t_exec *exec)
{
	struct stat	buff;

	signal(SIGQUIT, SIG_DFL);
	ft_pipe_last(cmd, exec);
	if (cmd->file_h && cmd->file_h->filename != NULL)
		redirection(cmd, exec);
	if (__get_var(GETEXIT, 0) == -1)
	{
		__get_var(SETEXIT, 1);
		exit(1);
	}
	if (cmd->path == NULL)
		print_error(cmd, ": command not found\n", 0);
	else
	{
		if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
		{
			stat(cmd->args[0], &buff);
			if (buff.st_mode & S_IFDIR)
				print_error(cmd, ": is a directory\n", 126);
		}
		execve(cmd->path, cmd->args, exec->env);
	}
}

void	one_command(t_cmds *cmd, t_exec *exec)
{
	int	pid;
	int	exitstatu;

	pid = fork();
	if (pid == 0)
	{
		child_proccess(cmd, exec);
		if (cmd->args[0] && strchr(cmd->args[0], '/'))
			ft_perror(cmd->args[0], ": No such file or directory\n");
		exit(127);
	}
	waitpid(pid, &exitstatu, 0);
	if (WIFEXITED(exitstatu))
		__get_var(SETEXIT, WEXITSTATUS(exitstatu));
	else if (WIFSIGNALED(exitstatu))
	{
		__get_var(SETEXIT, WTERMSIG(exitstatu) + 128);
		if (WTERMSIG(exitstatu) == SIGQUIT)
			write(2, "\\QUIT\n", 7);
	}
}

void	ft_execve(t_cmds *cmd, t_exec *exec)
{
	if (!cmd->next && !cmd->prec)
	{
		one_command(cmd, exec);
	}
	else
		ft_more_cmd(cmd, exec);
}

void	check_builtins_execve(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	if (cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "env") == 0)
			ft_env(exec);
		else if (ft_strcmp(cmd->args[0], "echo") == 0)
			echo(cmd);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			export(cmd, exec, header);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			unset(cmd, exec, header);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			pwd(cmd);
		else if (ft_strcmp(cmd->args[0], "cd") == 0)
			cd(cmd, header);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			ft_exit(cmd);
		else
			ft_execve(cmd, exec);
	}
}

void	dup_n_close(int out, int in)
{
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

void	check_builtins_condition(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(exec);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		export(cmd, exec, header);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		unset(cmd, exec, header);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		pwd(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		cd(cmd, header);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd);
}

void	check_builtins(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	int	in;
	int	out;

	out = dup(1);
	in = dup(0);
	if (cmd->file_h && cmd->file_h->filename != NULL)
		redirection(cmd, exec);
	if (__get_var(GETEXIT, 0) == -1)
	{
		__get_var(SETEXIT, 1);
		dup_n_close(out, in);
	}
	else
	{
		if (cmd->args[0])
			check_builtins_condition(cmd, exec, header);
		dup_n_close(out, in);
	}
}

int	is_builtin(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	if (cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "env") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			return (1);
		return (0);
	}
	return (0);
}

void	ft_cmds(t_exec *exec, t_cmds **cmd, t_headers *header)
{
	exec->pid[exec->i] = fork();
	if (exec->pid[exec->i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_pipe((*cmd), exec);
		if ((*cmd)->file_h && (*cmd)->file_h->filename != NULL)
			redirection((*cmd), exec);
		if (__get_var(GETEXIT, 0) == -1)
		{
			__get_var(SETEXIT, 1);
			exit(1);
		}
		check_builtins_execve((*cmd), exec, header);
		exit(__get_var(GETEXIT, 0));
	}
}

void	ft_simple_cmd(t_exec *exec, t_cmds *cmd, t_headers *header)
{
	pipe(exec->fd);
	exec->pid[exec->i] = fork();
	if (exec->pid[exec->i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_pipe_last(cmd, exec);
		if (cmd->file_h && cmd->file_h->filename != NULL)
			redirection(cmd, exec);
		if (__get_var(GETEXIT, 0) == -1)
		{
			__get_var(SETEXIT, 1);
			close(exec->fd[1]);
			close(exec->fd[0]);
			exit(1);
		}
		check_builtins_execve(cmd, exec, header);
		exit(__get_var(GETEXIT, 0));
	}
	close(exec->fd[1]);
	close(exec->fd[0]);
}

void	ft_last_cmd(t_exec *exec, t_cmds *cmd, t_headers *header)
{
	if (cmd && cmd->next == NULL)
	{
		if (cmd->prec != NULL)
			ft_simple_cmd(exec, cmd, header);
		else
		{
			if (is_builtin(cmd, exec, header) || !cmd->args[0])
				check_builtins(cmd, exec, header);
			else
				check_builtins_execve(cmd, exec, header);
		}
		if (exec->in != 0)
			close(exec->in);
	}
}

t_cmds	*commands(t_exec *exec, t_cmds *cmd, t_headers *header)
{
	while (cmd && cmd->next != NULL)
	{
		pipe(exec->fd);
		ft_cmds(exec, &cmd, header);
		if (exec->fd[1] > 2)
			close(exec->fd[1]);
		if (exec->in != 0)
			close(exec->in);
		exec->in = exec->fd[0];
		exec->i++;
		cmd = cmd->next;
	}
	return (cmd);
}

void	some_status_code(t_cmds *cmd, int *stat)
{
	if (cmd->prec)
	{
		if (WIFEXITED(*stat))
			__get_var(SETEXIT, WEXITSTATUS(*stat));
		else if (WIFSIGNALED(*stat))
		{
			__get_var(SETEXIT, WTERMSIG(*stat) + 128);
			if (WTERMSIG(*stat) == SIGQUIT)
				write(2, "QUIT\n", 6);
		}
	}
}

int	execute(t_headers *header)
{
	t_cmds	*cmd;
	t_exec	*exec;
	int		stat;
	int		i;

	__get_var(SETPID, -1);
	i = 0;
	exec = malloc(sizeof(t_exec));
	exec_init(header, exec);
	replace_arg(header, exec);
	cmd = header->cmd_h;
	cmd = commands(exec, cmd, header);
	ft_last_cmd(exec, cmd, header);
	while (i < exec->nb_cmd)
	{
		waitpid(exec->pid[i], &stat, 0);
		i++;
	}
	some_status_code(cmd, &stat);
	if (exec->in != 0)
		close(exec->in);
	exec_free(exec);
	__get_var(SETPID, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fidus <fidus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:38:46 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/20 22:12:57 by fidus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <limits.h>

typedef struct s_exec
{
	char	**path;
	char	**env;
	int		*fd;
	int		in;
	int		i;
	int		*pid;
	int		nb_cmd;
}t_exec;

int		g_exit_status;

t_env	*find_var_env(char *str, t_env *env);
void	ft_env(t_exec *exec);
void	cd(t_cmds *cmd);
int		execute(t_headers *header);
void	pwd(t_cmds *cmd);
void	echo(t_cmds *cmd);
void	export(t_cmds *cmd, t_exec *exec, t_headers *header);
void	unset(t_cmds *cmd, t_exec *exec, t_headers *header);
int		ft_exit(t_headers *headers);
void	ft_pipe(t_cmds *cmd, t_exec *exec);
void	ft_pipe_last(t_cmds *cmd, t_exec *exec);
void	fill_env(t_exec *exec, t_headers *header);
void	fill_env2(t_exec *exec, t_headers *header);

void	redirection(t_cmds *cmd_h, t_exec *exec);
#endif

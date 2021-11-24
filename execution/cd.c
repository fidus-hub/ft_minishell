/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:12 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 00:49:13 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	change_pwd(t_env *env, char *to_find, char *to_add)
{
	t_env	*pwd;
	char	*str;
	char	*to_free;

	str = 0;
	pwd = find_var_env(to_find, env);
	if (to_add)
		to_free = to_add;
	else
		to_free = getcwd(str, 0);
	free(pwd->val);
	pwd->val = ft_strdup_free(to_free);
	free(str);
}

void	only_cd(char *str, char *to_add, int *i, t_headers *header)
{
	str = getenv("HOME");
	if (str == 0)
		perror("minishell: cd: HOME not set\n");
	else
	{
		*i = chdir(str);
		if (!(*i))
			change_pwd(header->env_h, "OLDPWD", to_add);
	}
}

void	cd(t_cmds *cmd, t_headers *header)
{
	int		i;
	char	*str;
	char	*to_add;

	str = 0;
	to_add = getcwd(str, 0);
	i = 0;
	if (cmd->args[1] == NULL)
		only_cd(str, to_add, &i, header);
	else if (cmd->args[1])
	{
		i = chdir(cmd->args[1]);
		if (!i)
			change_pwd(header->env_h, "OLDPWD", to_add);
	}
	if (i != 0)
	{
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": No such file or directory\n", 29);
		free(to_add);
		__get_var(SETEXIT, 1);
	}
	else
		change_pwd(header->env_h, "PWD", 0);
}

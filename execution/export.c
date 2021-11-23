#include	"execution.h"

void	ft_error(char *c)
{
	write(2, "export: `", 9);
	write(2, c, ft_strlen(c));
	write(2, "': not a valid identifier\n", 27);
}

int	set_eq(char *str, int *eq, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '+' && str[*i + 1] != '=')
		{
			*eq = -1;
			ft_error(str);
			__get_var(SETEXIT, 1);
			break ;
		}
		else if (str[*i] == '+' && str[*i + 1] == '=')
		{
			*eq = 2;
			break ;
		}
		else if (str[*i] == '=')
		{
			*eq = 1;
			break ;
		}
		(*i)++;
		*eq = 0;
	}
	return (*i);
}

char	*check_eq(char *str, int *eq)
{
	int		i;
	int		k;
	char	*ret;

	ret = NULL;
	k = 0;
	i = 0;
	set_eq(str, eq, &i);
	if (*eq == 0 || *eq == -1)
		ret = ft_strdup(str);
	else if (*eq == 2 || *eq == 1)
	{
		ret = malloc(sizeof(char) * (i + 1));
		if (!ret)
			return (0);
		while (str[k] && k < i)
		{
			ret[k] = str[k];
			k++;
		}
		ret[k] = '\0';
	}
	return (ret);
}

char	*fill_exportval(char *str, int *eq)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] != '=')
			break ;
		else if (str[i] == '+' && str[i + 1] == '=')
			break ;
		else if (str[i] == '=')
			break ;
		i++;
	}
	if (*eq == 0 || *eq == -1)
		ret = NULL;
	else if (*eq == 1 || *eq == 2)
		ret = ft_strdup(&str[i + *eq]);
	return (ret);
}

t_env	*find_var_env(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->var) == 0)
			return (env);
		env = env->suivant;
	}
	return (NULL);
}

void	inside_fill(t_exec *exec, t_env *env)
{
	int	i;

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

void	fill_env2(t_exec *exec, t_headers *header)
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
	ft_free(exec->env);
	exec->env = NULL;
	exec->env = malloc(sizeof(char *) * (i + 1));
	env = header->env_h;
	inside_fill(exec, env);
}

void	only_export(t_cmds *cmd, t_env *env)
{
	if (!cmd->args[1])
	{
		while (env)
		{
			if (env->val != NULL)
			{
				printf("declare -x");
				printf(" %s=", env->var);
				printf("\"%s\"\n", env->val);
			}
			else
			{
				printf("declare -x ");
				printf("%s\n", env->var);
			}
			env = env->suivant;
		}
		__get_var(SETEXIT, 0);
	}
}

void	init_str(char **str, t_cmds *cmd, int *eq, int t)
{
	str[0] = check_eq(cmd->args[t], eq);
	str[1] = fill_exportval(cmd->args[t], eq);
	str[2] = 0;
}

void	add_to_export(t_cmds *cmd, t_env *env, t_headers *header, int t)
{
	int		eq;
	t_env	*exist_env;
	char	**str;

	str = malloc(sizeof(char *) * 3);
	init_str(str, cmd, &eq, t);
	exist_env = find_var_env(str[0], env);
	if (eq == 0 && !exist_env)
		ft_addbottom(header, str[0], NULL);
	else if (eq == 1 && exist_env)
	{
		free(exist_env->val);
		exist_env->val = ft_strdup_free(str[1]);
	}
	else if ((eq == 1 || eq == 2) && !exist_env)
		ft_addbottom(header, str[0], str[1]);
	else if (eq == 2 && exist_env)
		exist_env->val = ft_strjoin_free(exist_env->val, str[1]);
	if (((eq == 1 || eq == 2) && !exist_env) || (eq == 2 && exist_env))
		free(str[1]);
	free(str[0]);
	free(str);
}

void	export(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	int		t;
	t_env	*env;

	env = header->env_h;
	t = 1;
	only_export(cmd, env);
	while (cmd->args[t])
	{
		if (cmd->args[t][0] != '_' && ft_isalpha(cmd->args[t][0]) == 0)
		{
			ft_error(cmd->args[t]);
			__get_var(SETEXIT, 1);
		}
		else
		{
			add_to_export(cmd, env, header, t);
			if (__get_var(GETEXIT, 0) != 1)
				__get_var(SETEXIT, 0);
		}
		t++;
	}
	fill_env2(exec, header);
}

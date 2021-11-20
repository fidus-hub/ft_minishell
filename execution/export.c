#include	"execution.h"

char	*check_eq(char *str, int *eq)
{
	int	i;
	int	k;
	char	*ret;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] != '=')
		{
			*eq = -1;
			printf("export: `%s': not a valid identifier\n", str);
			__get_var(SETEXIT, 1);
			break;
		}
		else if (str[i] == '+' && str[i + 1] == '=')
		{
            *eq = 2;
            break;
        }
        else if (str[i] == '=')
        {
            *eq = 1;
            break;
        }
        i++;
        *eq = 0;
    }
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

char    *fill_exportval(char *str, int *eq)
{
    int i;
    int k;
    char *ret;

    i = 0;
    k = 0;
    while (str[i])
    {
        if (str[i] == '+' && str[i + 1] != '=')
            break;
        else if (str[i] == '+' && str[i + 1] == '=')
            break;
        else if (str[i] == '=')
            break;
        i++;
    }
    if (*eq == 0 || *eq == -1)
        ret = NULL;
    else if (*eq == 1 ||*eq == 2 )
        ret = ft_strdup(&str[i + *eq]);
    // else if (*eq == 2)
    //     ret = ft_strdup(str + i + 2);
    return (ret);
}

t_env   *find_var_env(char  *str, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(str, env->var) == 0)
            return (env);
        env = env->suivant;
    }
    return (NULL);
}

void	fill_env2(t_exec *exec, t_headers *header)
{
	int		i;
	t_env	*env;

	env = header->env_h;
	while (env)
	{
		if (env->val != NULL)
			i++;
		env = env->suivant;
	}
    ft_free(exec->env);
    exec->env=NULL;
	exec->env = malloc(sizeof(char *) * (i + 1));
    //printf("*%d\n",i);
	env = header->env_h;
	i = 0;
	while (env)
	{
		// if (env->val != NULL)
		// 	printf("%s=%s\n", env->var, env->val);
		if (env->val != NULL)
		{
			exec->env[i] = ft_strjoin(env->var, "=");
			exec->env[i] = ft_strjoin_free(exec->env[i], env->val);
			i++;
		}
		env = env->suivant;
	}
   // printf("**%d\n",i);
	exec->env[i] = 0;
	// i = 0;
	// while (exec->env[i])
	// {
	// 	printf("%s\n", exec->env[i]);
	// 	i++;
	// }
}

void    export(t_cmds *cmd, t_exec *exec, t_headers *header)
{
    int t;
    int k;
    int eq;
    t_env *exist_env;
    t_env *env;
    char **str;

    env = header->env_h;
    k = 0;
    t = 1;
    if (!cmd->args[t])
    {
        while (env)
        {
            if (env->val != NULL)
            {
                printf("declare -x");
                printf(" %s=", env->var);
                printf("\"%s\"\n", env->val);
            }else
            {
                printf("declare -x ");
                printf("%s\n", env->var);  
            }
            env = env->suivant;
        }
        __get_var(SETEXIT,0);
    }
    env = header->env_h;
    while (cmd->args[t])
    {
        eq = 0;
        //eq==0 no =
        //eq==1 =
        //eq==2 +=
        //eq==-1 error not a valid identifier
        k = 0;
        if (cmd->args[t][0] != '_' && ft_isalpha(cmd->args[t][0]) == 0)
        {
            printf("export: `%s': not a valid identifier\n", cmd->args[t]);
            __get_var(SETEXIT,1);
            // break ;
        }
        else
        {
            str = malloc(sizeof(char *) * 3);
            str[0] = check_eq(cmd->args[t], &eq);
            str[1] = fill_exportval(cmd->args[t], &eq);
            str[2] = 0;
            // printf("%s||%s||*%d*\n", str[0], str[1],eq);
            exist_env = find_var_env(str[0], env);
            if (eq == 0 && !exist_env)
            {
    			ft_addbottom(header, str[0], NULL);
    			//add it with val = NULL
    		}
            else if (eq == 1 && exist_env)
            {
    			exist_env->val = ft_strdup_free(str[1]);
    			//modify it
    		}
            else if (eq == 1  && !exist_env)
            {
    			ft_addbottom(header, str[0], str[1]);
                free(str[1]);
    			//add it with val = 
    		}
            else if (eq == 2  && exist_env)
            {
    			exist_env->val = ft_strjoin_free(exist_env->val, str[1]);
    			//add it with val += 
    		}
            else if (eq == 2  && !exist_env)
            {
    			ft_addbottom(header, str[0], str[1]);
                free(str[1]);
    			//add it with val = 
    		}
            free(str[0]);
            free(str);
            if (__get_var(GETEXIT,0) != 1)
                __get_var(SETEXIT,0);  
        }
        t++;
    }
    fill_env2(exec, header);
}

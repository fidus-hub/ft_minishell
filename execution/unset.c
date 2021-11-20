#include    "execution.h"

void    unset(t_cmds *cmd, t_exec *exec, t_headers *header)
{
    int t;
    t_env	*exist_env;
    t_env	*to_del;
    t_env	*env;
    char	*str;

    // env = header->env_h;
    t = 1;
    env = header->env_h;
    while (cmd->args[t])
    {
        //eq==0 no =
        //eq==1 =
        //eq==2 +=
        //eq==-1 error not a valid identifier
        // k = 0;
        if (cmd->args[t][0] != '_' && ft_isalpha(cmd->args[t][0]) == 0)
        {
            printf("export: `%s': not a valid identifier\n", cmd->args[t]);
            __get_var(SETEXIT,1);
            // break ;
        }
        else
        {
            str = ft_strdup(cmd->args[t]);
            // printf("%s||%s||*%d*\n", str[0], str[1],eq);
            to_del = find_var_env(str, env);
            if (to_del)
            {
                // while (env && ft_strcmp(env->var, str) == 0)
                // {
                if (to_del->preced == NULL && to_del->suivant)
                {
                    exist_env = to_del->suivant;
                    header->env_h = exist_env;
                    exist_env->preced = NULL;
                    if (to_del->val != NULL)
				        free(to_del->val);
                    if (to_del->var != NULL)
                        free(to_del->var);
                    free(to_del);
					to_del = NULL;
                }
                else if (to_del->preced && to_del->suivant)
                {
                    exist_env = to_del->suivant;
                    exist_env->preced = to_del->preced;
                    exist_env = to_del->preced;
                    exist_env->suivant = to_del->suivant;
                    if (to_del->val != NULL)
				        free(to_del->val);
                    if (to_del->var != NULL)
                        free(to_del->var);
                    free(to_del);
					to_del = NULL;
                }
                else if (to_del->preced && to_del->suivant == NULL)
                {
                   // header->env_f = to_del->preced;
                    exist_env = to_del->preced;
                    exist_env->suivant = NULL;
                    header->env_f = exist_env;
                    // exist_env->suivant = to_del->suivant;
                    if (to_del->val != NULL)
				        free(to_del->val);
                    if (to_del->var != NULL)
                        free(to_del->var);
                    free(to_del);
					to_del = NULL;
                }
    		}
            free(str);
            if (__get_var(GETEXIT,0) != 1)
                __get_var(SETEXIT,0);
        }
        t++;
    }
    fill_env2(exec, header);
}

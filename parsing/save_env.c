#include "../minishell.h"

void	ft_delbottom(t_headers *head)
{
	t_env	*to_delete;
	t_env	*stack;
	//printf("%s\n", head->env_h->var);
	if (head != NULL && head->env_h != NULL)
	{
		to_delete = head->env_f;
		if (!to_delete->preced)
		{
			if (to_delete->val != NULL)
				free(to_delete->val);
			if (to_delete->var != NULL)
				free(to_delete->var);
			free(to_delete);
			head->env_h = NULL;
			head->env_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->preced;
			head->env_f = stack;
			stack->suivant = NULL;
			if (to_delete->val != NULL)
				free(to_delete->val);
			if (to_delete->var != NULL)
				free(to_delete->var);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

void	ft_addbottom(t_headers *head, char *var, char *val)
{
	t_env	*stack;
	t_env	*to_add;

	to_add = malloc(sizeof(t_env));
	if (!to_add)
		exit(0);
	if (head->env_h == NULL)
	{
		if (var != NULL)
			to_add->var = ft_strdup(var);
		if (val != NULL)
			to_add->val = ft_strdup(val);
		else
			to_add->val = NULL;
		to_add->suivant = NULL;
		to_add->preced = NULL;
		head->env_f = to_add;
		head->env_h = to_add;
	}
	else
	{
		stack = head->env_f;
		if (var != NULL)
			to_add->var = ft_strdup(var);
		if (val != NULL)
			to_add->val = ft_strdup(val);
		else
			to_add->val = NULL;
		to_add->preced = stack;
		to_add->suivant = NULL;
		stack->suivant = to_add;
		head->env_f = to_add;
	}
}

void	from_tab_to_ll(char **env, t_headers *header)
{
	int i;
	char **str;

	i = 0;
	while(env[i])
	{
		str = ft_split(env[i], '=');
		ft_addbottom(header, str[0], str[1]);
		ft_free(str);
		i++;
	}
}

void	envi(char **env, t_headers *header)
{
	// t_env		*new_env;

	// new_env = NULL;
	from_tab_to_ll(env, header);
	// new_env = header->env_h;
	// while (new_env)
	// {
	// 	printf("%s = %s\n", new_env->var, new_env->val);
	// 	new_env = new_env->suivant;
	// }
	// while (header->env_h)
	// 	ft_delbottom(header);
}


// char	**env_from_ll_to_tab(t_henv *henv)
// {
// 	int i;
// 	t_env *nb;
// 	int k;
// 	int r;
// 	char **str;

// 	k = 0;
// 	i = 0;
// 	nb = henv->env_h;
// 	while (nb)
// 	{
// 		i++;
// 		nb = nb->suivant;
// 	}
// 	str = malloc(sizeof(char) * i + 1);
// 	nb = henv->header;
// 	while(nb)
// 	{
// 		k = 0;
// 		while (nb->val[k])
// 			k++;
// 		while (nb->var[])
// 		nb = nb->suivant;
// 	}
// 	i = 0;
// 	// while(env[i])
// 	// {
// 	// 	str = ft_split(env[i], '=');
// 	// 	ft_addbottom(henv, str[0], str[1]);
// 	// 	ft_freee(str, ft_mots(env[i], '=') + 1);
// 	// 	i++;
// 	// }
// 	return (str);
// }

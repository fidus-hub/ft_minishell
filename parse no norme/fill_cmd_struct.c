#include "../minishell.h"

void	ft_addbotcmd_help(t_cmds *to_add)
{
	to_add->file_h = NULL;
	to_add->file_f = NULL;
	to_add->path = NULL;
	to_add->next = NULL;
	to_add->args = NULL;
}

void	ft_addbotcmd(t_headers *head, char *val)
{
	t_cmds	*stack;
	t_cmds	*to_add;

	to_add = malloc(sizeof(t_cmds));
	if (!to_add)
		exit(0);
	if (head->cmd_h == NULL)
	{
		to_add->cmd = ft_strdup(val);
		ft_addbotcmd_help(to_add);
		to_add->prec = NULL;
		head->cmd_f = to_add;
		head->cmd_h = to_add;
	}
	else
	{
		stack = head->cmd_f;
		to_add->cmd = ft_strdup(val);
		ft_addbotcmd_help(to_add);
		to_add->prec = stack;
		stack->next = to_add;
		head->cmd_f = to_add;
	}
}

void	ft_freefile(t_cmds *head)
{
	while (head->file_h)
		ft_delbotfile(head);
}

void	ft_delbotcmd_help(t_cmds *to_delete)
{
	ft_freefile(to_delete);
	ft_free(to_delete->args);
	free(to_delete->cmd);
	if (to_delete->path != NULL)
		free(to_delete->path);
}

void	ft_delbotcmd(t_headers *head)
{
	t_cmds	*to_delete;
	t_cmds	*stack;

	if (head != NULL && head->cmd_h != NULL)
	{
		to_delete = head->cmd_f;
		if (!to_delete->prec)
		{
			ft_delbotcmd_help(to_delete);
			free(to_delete);
			head->cmd_h = NULL;
			head->cmd_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->prec;
			head->cmd_f = stack;
			stack->next = NULL;
			ft_delbotcmd_help(to_delete);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

void	ft_complet(t_headers *header)
{
	t_cmds	*new_cmd;

	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		new_cmd->args = ft_flex(new_cmd->cmd, ' ');
		new_cmd = new_cmd->next;
	}
}

void	fill_cmd(t_headers *header, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_addbotcmd(header, str[i]);
		i++;
	}
}

char	*to_find(char *str, int k)
{
	int		i;
	int		r;
	char	*var;

	i = 0;
	r = k + 1;
	while (str[r] && str[r] != '"' && str[r] != ' ' && str[r] != '\'' && str[r]
		!= '$' && str[r] != '=' && str[r] != '>' && str[r] != '<')
	{
		i++;
		r++;
	}
	var = malloc(sizeof(char) * (i + 2));
	r = i + 1;
	i = 0;
	while (i < r /*str[k] && str[k] != '"' && str[k] != ' ' && str[k] != '\'' && str[k] != '$'*/)
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

static int ft_intlen(unsigned int nb)
{
	int i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char *ft_itoa(int c)
{
	unsigned int nb;
	unsigned int i;
	char *str;

	nb = c;
	i = 0;
	if (c <= 0)
	{
		nb = -c;
		i = 1;
	}
	i += ft_intlen(nb);
	if (!(str = (char *)malloc((i + 1) * sizeof(char))))
		return (0);
	str[i] = '\0';
	while (i-- > 0)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (c < 0)
		str[0] = '-';
	return (str);
}

char *print_exitstat(char *str, char *var)
{
	str = ft_itoa(__get_var(GETEXIT, 0));
	if (var[2])
		str = ft_strjoin_free(str, var + 2);
	return (str);
}

char *findit(t_headers *header, char *var)
{
	t_env *checkenv;
	char *str;

	str = NULL;
	checkenv = header->env_h;
	if (var[1] == '?')
		return (print_exitstat(str, var));
	if (var[1] != '_' && !ft_isalpha(var[1]))
	{
		var += 2;
		return (ft_strdup(var));
	}
	var++;
	while (checkenv)
	{
		if (!ft_strcmp(checkenv->var, var) && checkenv->val)
		{
			str = ft_strdup(checkenv->val);
			return (str);
		}
		checkenv = checkenv->suivant;
	}
	str = malloc(1);
	*str = '\0';
	return (str);
}

int calculate_dollar(char *str, int i)
{
	int d;

	d = 0;
	while (str[i] && str[i] == '$')
	{
		i++;
		d++;
	}
	return (d);
}

void check_dollarquotes(int *s_q, int *d_q, char c)
{
	if (c == '\'' && (*d_q % 2) == 0)
		(*s_q)++;
	if (c == '"' && (*s_q % 2) == 0)
		(*d_q)++;
}

void dollar_is_here(t_cmds *new_cmd, int *i, t_headers *header)
{
	char *var;
	char *val;
	char *rest;

	var = to_find(new_cmd->cmd, *i);
	rest = ft_strdup(ft_strstr(new_cmd->cmd + (*i), var));
	val = findit(header, var);
	// printf("[%s], [%s], [%s]\n", var, val, rest);
	new_cmd->cmd = ft_strjoin_dollarfree(new_cmd->cmd, val, *i);
	new_cmd->cmd = ft_strjoin_free(new_cmd->cmd, rest);
	(*i) = -1;
	free(var);
	free(val);
	free(rest);
}

void	dollar_calcul(char *str, int *i, int *d)
{
	if (str[*i] == '$')
	{
		(*d) = calculate_dollar(str, *i);
		(*i) += (*d - 1);
	}
}

void checkdollar_cmd(t_headers *header)
{
	t_cmds *new_cmd;
	int i;
	int s_q;
	int d_q;
	int d;

	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		d = 0;
		i = 0;
		s_q = 0;
		d_q = 0;
		while (new_cmd->cmd[i])
		{
			check_dollarquotes(&s_q, &d_q, new_cmd->cmd[i]);
			dollar_calcul(new_cmd->cmd, &i, &d);
			if (new_cmd->cmd[i] == '$' && (d % 2) && new_cmd->cmd[i + 1] != '\0' && new_cmd->cmd[i + 1] != '"' && new_cmd->cmd[i + 1] != '=' && new_cmd->cmd[i + 1] != '+' && new_cmd->cmd[i + 1] != '-' && s_q % 2 == 0)
				dollar_is_here(new_cmd, &i, header);
			i++;
		}
		new_cmd = new_cmd->next;
	}
}

void save_cmd(t_headers *header, char **str)
{
	t_cmds *new_cmd;
	t_file *file;
	int		i;

	fill_cmd(header, str);
	checkdollar_cmd(header);
	i = checkredirection_cmd(header->cmd_h);
	ft_complet(header);
	if (header->cmd_h)
		if (i != -1 && (header->cmd_h->args[0] || header->cmd_h->file_h))
			execute(header);
	// new_cmd = header->cmd_h;
	// file = file->next;// 	new_cmd = header->cmd_h;
	// while (new_cmd)
	// {
	// 	file = new_cmd->file_h;
	// 	int i = 0;
	// 	printf("|%s|\n",new_cmd->cmd);
	// 	while (new_cmd->args[i])
	// 	{
	// 			printf("arg:%d ==> %s\n",i,new_cmd->args[i]);
	// 			i++;
	// 	}
	// 		while (file)
	// 	{
	// 		printf("[type:%d][name:%s]\n",file->type,file->filename);
	// 		printf("[%s]\n",file->filename);
	// 		file = file->next;
	// 	}
	// 	printf("----------------------\n");
	// 	new_cmd = new_cmd->next;
	// }
	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		file = new_cmd->file_h;
		while (file)
		{
			if (file->type == 4)
				unlink(file->filename);
			file = file->next;
		}
		new_cmd = new_cmd->next;
	}
	while (header->cmd_h)
		ft_delbotcmd(header);
	// system("leaks minishell");
	// save(header, str);
}
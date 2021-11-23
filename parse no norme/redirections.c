#include "../minishell.h"

void	ft_addbotfile_helper(t_file	*to_add, char *val)
{
	if (val != NULL)
		to_add->filename = ft_strdup(val);
	else
		to_add->filename = ft_strdup("");
}

void	ft_addbotfile(t_cmds *head, char *val, int type)
{
	t_file	*stack;
	t_file	*to_add;

	to_add = malloc(sizeof(t_file));
	if (!to_add)
		exit(0);
	if (head->file_h == NULL)
	{
		ft_addbotfile_helper(to_add, val);
		to_add->type = type;
		to_add->next = NULL;
		to_add->prec = NULL;
		head->file_f = to_add;
		head->file_h = to_add;
	}
	else
	{
		stack = head->file_f;
		ft_addbotfile_helper(to_add, val);
		to_add->type = type;
		to_add->prec = stack;
		to_add->next = NULL;
		stack->next = to_add;
		head->file_f = to_add;
	}
}

void	ft_delbotfile(t_cmds *head)
{
	t_file	*to_delete;
	t_file	*stack;

	if (head != NULL && head->file_h != NULL)
	{
		to_delete = head->file_f;
		if (!to_delete->prec)
		{
			free(to_delete->filename);
			free(to_delete);
			head->file_h = NULL;
			head->file_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->prec;
			head->file_f = stack;
			stack->next = NULL;
			free(to_delete->filename);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

int	redcounter(char *str, int i)
{
	int	d;

	d = 0;
	while (str[i] && str[i] == '$')
	{
		i++;
		d++;
	}
	return (d);
}

void	type_of_red(char *str, int r, int *red)
{
	if (str[r] == '>' && str[r + 1] != '>')
		*red = ONE;
	else if (str[r] == '>' && str[r + 1] == '>')
		*red = TWO;
	else if (str[r] == '<' && str[r + 1] != '<')
		*red = ONEREV;
	else if (str[r] == '<' && str[r + 1] == '<')
		*red = TWOREV;
}

void	skip_it(char *str, int *i, int r)
{
	while (str[r] == '>' || str[r] == '<' || str[r] == ' ')
		laysameh(&r, i);
	while (str[r] && str[r] != ' ' && str[r] != '>' && str[r] != '<')
	{
		if (str[r] == '"')
		{
			laysameh(&r, i);
			while (str[r] && str[r] != '"')
				laysameh(&r, i);
			laysameh(&r, i);
		}
		else if (str[r] == '\'')
		{
			laysameh(&r, i);
			while (str[r] && str[r] != '\'')
				laysameh(&r, i);
			laysameh(&r, i);
		}
		else
			laysameh(&r, i);
	}
}

char	*find_red(char *str, int k, int *red)
{
	int		i;
	int		r;
	char	*var;

	i = 0;
	r = k;
	type_of_red(str, r, red);
	skip_it(str, &i, r);
	var = malloc(sizeof(char) * (i + 1));
	r = i;
	i = 0;
	while (i < r)
		var[i++] = str[k++];
	var[i] = '\0';
	return (var);
}

void	findredtosave_help(char	*var, int *k, int *i)
{
	if (var[*i] == '"')
	{
		(*i)++;
		while (var[*i] && var[*i] != '"')
		{
			(*k)++;
			(*i)++;
		}
		(*i)++;
	}
	else if (var[*i] == '\'')
	{
		(*i)++;
		while (var[*i] && var[*i] != '\'')
		{
			(*k)++;
			(*i)++;
		}
		(*i)++;
	}
	else
	{
		(*i)++;
		(*k)++;
	}
}

char	*findredtosave_help2(char *var, int *k, int t)
{
	char	*ret;

	ret = malloc(sizeof(char) * ((*k) + 1));
	*k = 0;
	while (var[t] && var[t] != '>' && var[t] != '<' && var[t] != ' ')
	{
		if (var[t] == '\'')
		{
			t++;
			while (var[t] != '\'')
				ret[(*k)++] = var[t++];
			t++;
		}
		else if (var[t] == '"')
		{
			t++;
			while (var[t] != '"')
				ret[(*k)++] = var[t++];
			t++;
		}
		else
			ret[(*k)++] = var[t++];
	}
	ret[*k] = '\0';
	return (ret);
}

char	*findredtosave(char *var)
{
	int		i;
	int		k;
	int		t;

	k = 0;
	t = 0;
	i = 0;
	while (var[i] == '>' || var[i] == '<' || var[i] == ' ')
		var++;
	while (var[i] && var[i] != '>' && var[i] != '<' && var[i] != ' ')
		findredtosave_help(var, &k, &i);
	return (findredtosave_help2(var, &k, t));
}

char	*ft_strjoin_redfree(char *s1, char *s2, int i)
{
	char	*ret;

	ret = ft_strjoin_red(s1, s2, i);
	free (s1);
	return (ret);
}

char	*ft_herdocs_rl_helper(char *ret, char *line)
{
	if (ret == NULL)
	{
		ret = ft_strdup(line);
		ret = ft_strjoin_free(ret, "\n");
	}
	else
	{
		ret = ft_strjoin_free(ret, line);
		ret = ft_strjoin_free(ret, "\n");
	}
	free(line);
	return (ret);
}

void	handle_sigint_herdoc(int sigint)
{
	(void)sigint;
	write(1, "\n", 1);
	__get_var(SETEXIT, 1);
	exit(1);
}

void	ft_herdocs_rl(char	*limiter, int fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handle_sigint_herdoc);
		line = readline("heredoc>");
		if (!line)
		{
			__get_var(SETEXIT, 0);
			exit(0);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			__get_var(SETEXIT, 0);
			exit(0);
		}
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

char	*ft_herdocs(char *str)
{
	char	*limiter;
	int		pid;
	char	*name;
	int		fd;
	int		status;

	limiter = findredtosave(str);
	name = ft_strjoin("/tmp/", limiter);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	__get_var(SETPID, -1);
	pid = fork();
	if (pid == 0)
		ft_herdocs_rl(limiter, fd);
	waitpid(pid, &status, 0);
	if (status == 256)
		__get_var(SETEXIT, 1);
	__get_var(SETPID, 0);
	free(limiter);
	close(fd);
	return (name);
}

void	check_redquotes(int	*s_q, int *d_q, char c)
{
	if (c == '\'')
		(*s_q)++;
	if (c == '"')
		(*d_q)++;
}

void	file_is_here(t_cmds *find_redirection, int *red, int *i)
{
	char	*var;
	char	*val;
	char	*rest;

	var = find_red(find_redirection->cmd, *i, red);
	rest = ft_strdup(ft_strstr(find_redirection->cmd + (*i), var));
	if (*red == 4)
		val = ft_herdocs(var);
	else
		val = findredtosave(var);
	find_redirection->cmd = ft_strjoin_redfree(find_redirection->cmd, rest, *i);
	ft_addbotfile(find_redirection, val, *red);
	(*i) = -1;
	free(var);
	free(val);
	free(rest);
}

int	checkredirection_cmd(t_cmds	*find_redirection)
{
	int	red;
	int	s_q;
	int	d_q;
	int	i;

	while (find_redirection)
	{
		i = -1;
		red = 0;
		s_q = 0;
		d_q = 0;
		while (find_redirection->cmd[++i])
		{
			check_redquotes(&s_q, &d_q, find_redirection->cmd[i]);
			if ((find_redirection->cmd[i] == '>'
					|| find_redirection->cmd[i] == '<') && !(d_q % 2)
				&& !(s_q % 2))
			{
				file_is_here(find_redirection, &red, &i);
			}
		}
		find_redirection = find_redirection->next;
	}
	return (1);
}

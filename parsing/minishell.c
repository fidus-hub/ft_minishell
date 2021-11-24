/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:03:06 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 01:10:02 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_deltop_helper(t_env *to_delete)
{
	free(to_delete->val);
	free(to_delete->var);
}

void	ft_deltop(t_headers *head)
{
	t_env	*to_delete;
	t_env	*stack;

	if (head != NULL && head->env_h != NULL)
	{
		to_delete = head->env_h;
		if (!to_delete->suivant)
		{
			ft_deltop_helper(to_delete);
			free(to_delete);
			head->env_h = NULL;
			head->env_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->suivant;
			head->env_h = stack;
			stack->preced = NULL;
			ft_deltop_helper(to_delete);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

void	ft_addtop(t_headers *head, char *var, char *val)
{
	t_env	*stack;
	t_env	*to_add;

	to_add = malloc(sizeof(t_env));
	if (!to_add)
		exit(0);
	if (head->env_h == NULL)
	{
		to_add->var = ft_strdup(var);
		to_add->val = ft_strdup(val);
		to_add->suivant = NULL;
		to_add->preced = NULL;
		head->env_f = to_add;
		head->env_h = to_add;
	}
	else
	{
		stack = head->env_h;
		to_add->var = ft_strdup(var);
		to_add->val = ft_strdup(val);
		to_add->suivant = stack;
		to_add->preced = NULL;
		stack->preced = to_add;
		head->env_h = to_add;
	}
}

void	parse(char *line, t_headers *header)
{
	char	**str;

	if (!check_error(line))
	{
		str = split_pipe(line, header);
		save_cmd(header, str);
		ft_free(str);
	}
}

void	handle_sigint(int sigint)
{
	(void)sigint;
	if (__get_var(GETPID, 0) == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		__get_var(SETEXIT, 1);
	}
}

int	__get_var(t_norm op, int value)
{
	static int		exit_status = 0;
	static int		pids = 0;

	if (op == GETEXIT)
		return (exit_status);
	if (op == SETEXIT)
		exit_status = value;
	if (op == SETPID)
		pids = value;
	if (op == GETPID)
		return (pids);
	return (0);
}

void	ft_readline(t_headers *header)
{
	char		*line;
	int			k;

	k = 1;
	line = NULL;
	while (k)
	{
		line = readline("minishell🔥\%");
		if (!line)
		{
			printf("exit\n");
			while (header->env_h != NULL)
				ft_delbottom(header);
			free(header);
			header = NULL;
			exit(__get_var(GETEXIT, 0));
		}
		parse(line, header);
		add_history(line);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_headers	*header;

	(void) ac;
	(void) av;
	__get_var(SETPID, 0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	header = malloc(sizeof(t_headers));
	header->env_h = NULL;
	header->env_f = NULL;
	header->cmd_h = NULL;
	envi(env, header);
	ft_readline(header);
	while (header->env_h != NULL)
		ft_delbottom(header);
	free(header);
	header = NULL;
}

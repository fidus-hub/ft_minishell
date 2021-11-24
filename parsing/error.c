/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:01:03 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 02:00:47 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_check_error(char *str)
{
	write(2, "minishell: ", 12);
	write(2, "syntax error near unexpected token `", 36);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 3);
	__get_var(SETEXIT, 258);
	return (1);
}

void	nb_of_dq(char *line, int *d_q, int *i)
{
	(*d_q) = 1;
	(*i)++;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] == '"')
	{
		(*d_q) = 0;
		(*i)++;
	}
}

void	nb_of_sq(char *line, int *s_q, int *i)
{
	(*s_q) = 1;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
	{
		(*s_q) = 0;
		(*i)++;
	}
}

int	nb_of_quotes(char *line)
{
	int	i;
	int	d_q;
	int	s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (line[i])
	{
		if (line[i] == '"')
			nb_of_dq(line, &d_q, &i);
		else if (line[i] == '\'')
			nb_of_sq(line, &s_q, &i);
		else
			i++;
	}
	if (s_q || d_q)
	{
		printf("syntax error in quotes\n");
		return (1);
	}
	return (0);
}

int	check_space(char *line, int i)
{
	if (line[i] == '|')
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '|' || line[i] == '\0')
			return (1);
	}
	return (0);
}

int	check_error_pipes(char *line)
{
	int	i;
	int	d_q;

	d_q = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (print_check_error("|"));
	while (line[i])
	{
		if (line[i] == '"')
			d_q++;
		if ((line[i] == '|' && !line[i + 1])
			|| (check_space(line, i) && d_q % 2 == 0))
			return (print_check_error("|"));
		if ((d_q % 2 == 0 && (line[i] == '<' || line[i] == '>')
				&& line[i + 1] == '|'))
			return (print_check_error("newline"));
		i++;
	}
	return (0);
}

int	rederror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			i += 2;
			while (str[i] == ' ')
				i++;
			if (!str[i] || str[i] == '>' || str[i] == '<' || str[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_error_redirections(char *line)
{
	int	i;
	int	d_q;

	i = 0;
	d_q = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '"')
			d_q++;
		if (line[i] == '<' && rederror(line) && (d_q % 2) == 0)
			return (print_check_error("newline"));
		else if ((line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
			|| (line[i] == '>' && line[i + 1] == '|'))
			return (print_check_error("<"));
		else if ((line[i] == '>' && line[i + 1] == '<'))
			return (print_check_error("<"));
		else if (line[i] == '>' && rederror(line) && (d_q % 2) == 0)
			return (print_check_error(">"));
		i++;
	}
	return (0);
}

int	only_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && line[i + 1] && line[i] == '"' && line[i + 1] == '"')
	{
		printf("minishell: : command not found\n");
		__get_var(SETEXIT, 127);
		return (1);
	}
	return (0);
}

int	check_error(char *line)
{
	(void)line;
	if (only_quotes(line))
		return (1);
	else if (nb_of_quotes(line))
		return (1);
	else if (check_error_pipes(line))
		return (1);
	else if (check_error_redirections(line))
		return (1);
	else
		return (0);
}

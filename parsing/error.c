/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:01:03 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 01:01:35 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		{
			d_q = 1;
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] == '"')
			{
				d_q = 0;
				i++;
			}
		}
		else if (line[i] == '\'')
		{
			s_q = 1;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] == '\'')
			{
				s_q = 0;
				i++;
			}
		}
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
		while (line[i + 1] == ' ')
			i++;
		if (line[i + 1] == '|')
			return (1);
	}
	return (0);
}

int	check_error_pipes(char *line)
{
	int	i;
	int	d_q;
	int	k;

	d_q = 0;
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		__get_var(SETEXIT, 258);
		return (1);
	}
	while (line[i])
	{
		if (line[i] == '"')
			d_q++;
		if ((line[i] == '|' && !line[i + 1])
			|| (check_space(line, i) && d_q % 2 == 0))
		{
			__get_var(SETEXIT, 258);
			printf("syntax error near unexpected token `|'\n");
			return (1);
		}
		if ((d_q % 2 == 0 && (line[i] == '<' || line[i] == '>')
				&& line[i + 1] == '|'))
		{
			__get_var(SETEXIT, 258);
			printf("syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (line[i] == '|')
		{
			k = i + 1;
			while (line[k] == ' ')
				k++;
			if (line[k] == '\0')
			{
				__get_var(SETEXIT, 258);
				printf("syntax error near unexpected token `|'\n");
				return (1);
			}
		}
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
		{
			printf("syntax error near unexpected token `newline'\n");
			__get_var(SETEXIT, 258);
			return (1);
		}
		else if ((line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
			|| (line[i] == '>' && line[i + 1] == '|'))
		{
			printf("syntax error near unexpected token `<'\n");
			__get_var(SETEXIT, 258);
			return (1);
		}
		else if ((line[i] == '>' && line[i + 1] == '<'))
		{
			printf("syntax error near unexpected token `<'\n");
			__get_var(SETEXIT, 258);
			return (1);
		}
		else if (line[i] == '>' && rederror(line) && (d_q % 2) == 0)
		{
			printf("minishell: syntax error near unexpected token `>'\n");
			__get_var(SETEXIT, 258);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_error(char *line)
{
	(void)line;
	if (nb_of_quotes(line))
		return (1);
	else if (check_error_pipes(line))
		return (1);
	else if (check_error_redirections(line))
		return (1);
	else
		return (0);
}

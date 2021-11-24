/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:03:22 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 01:03:23 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_mots_helper(char const *s, int	*i)
{
	if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '"')
			(*i)++;
	}
	else if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
}

static	int	ft_mots(char const *s, char c)
{
	int			i;
	int			k;
	int			p;
	int			d_q;

	d_q = 0;
	i = 0;
	k = 0;
	p = 1;
	if (*s)
	{
		while (s[i])
		{
			ft_mots_helper(s, &i);
			if (s[i] == c)
				p = 1;
			else if (p == 1 && !d_q)
			{
				p = 0;
				k++;
			}
			i++;
		}
	}
	return (k);
}

static void	*ft_freee(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (0);
}

void	laysameh(int *r, int *i)
{
	(*r)++;
	(*i)++;
}

static int	ft_alpha(char const *s, char c, int i)
{
	int	r;

	r = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
		{
			laysameh(&r, &i);
			while (s[i] != '"')
				laysameh(&r, &i);
			laysameh(&r, &i);
		}
		else if (s[i] == '\'')
		{
			laysameh(&r, &i);
			while (s[i] != '\'')
				laysameh(&r, &i);
			laysameh(&r, &i);
		}
		else
			laysameh(&r, &i);
	}
	return (r);
}

void	ft_remp_helper2(t_toke *toke, char **p, char const *s)
{
	p[toke->j][toke->k] = s[toke->i];
	toke->k++;
	toke->i++;
}

void	ft_remp_helper(t_toke *toke, char **p, char const *s)
{
	if (s[toke->i] == '"')
	{
		ft_remp_helper2(toke, p, s);
		while (s[toke->i] != '"')
		{
			ft_remp_helper2(toke, p, s);
		}
		ft_remp_helper2(toke, p, s);
	}
	else if (s[toke->i] == '\'')
	{
		ft_remp_helper2(toke, p, s);
		while (s[toke->i] != '\'')
		{
			ft_remp_helper2(toke, p, s);
		}
		ft_remp_helper2(toke, p, s);
	}
	else
		p[toke->j][toke->k++] = s[toke->i++];
}

static char	**ft_remp(char **p, char const *s, char c, int mots)
{
	t_toke	*toke;

	toke = malloc(sizeof(t_toke));
	toke->i = 0;
	toke->j = 0;
	while (s[toke->i] && mots > toke->j)
	{
		toke->k = 0;
		while (s[toke->i] == c)
			s++;
		p[toke->j] = malloc(sizeof(char) * ft_alpha(s, c, toke->i) + 1);
		if (!p[toke->j])
			return (ft_freee(p));
		while (s[toke->i] && s[toke->i] != c)
		{
			ft_remp_helper(toke, p, s);
		}
		p[toke->j][toke->k] = '\0';
		toke->j++;
	}
	p[toke->j] = 0;
	free(toke);
	return (p);
}

char	**ft_toke(char const *s, char c)
{
	char	**p;
	int		mots;

	if (s == NULL)
		return (0);
	mots = ft_mots(s, c);
	p = malloc(sizeof(char *) * (mots + 1));
	if (!p)
		return (0);
	return (ft_remp(p, s, c, mots));
}

char	**split_pipe(char *line, t_headers *header)
{
	char	**test;

	(void)header;
	test = ft_toke(line, '|');
	return (test);
}

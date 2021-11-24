/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrissen <mgrissen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:02:36 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 01:02:37 by mgrissen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static	int	ft_mots(char const *s, char c)
{
	int			i;
	int			k;
	int			p;

	i = 0;
	k = 0;
	p = 1;
	while (s[i])
	{
		if (s[i] == c)
			p = 1;
		else if (p == 1)
		{
			p = 0;
			k++;
		}
		i++;
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

static int	ft_alpha(char const *s, char c, int i)
{
	int	r;

	r = 0;
	while (s[i] && s[i] != c)
	{
		r++;
		i++;
	}
	return (r);
}

static char	**ft_remp(char **p, char const *s, char c, int mots)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] && mots > j)
	{
		k = 0;
		while (s[i] == c)
			s++;
		p[j] = malloc(sizeof(char) * ft_alpha(s, c, i) + 1);
		if (!p[j])
			return (ft_freee(p));
		while (s[i] && s[i] != c)
			p[j][k++] = s[i++];
		p[j][k] = '\0';
		j++;
	}
	p[j] = 0;
	return (p);
}

char	**ft_split(char const *s, char c)
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

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

// int	main(int ac, char **av, char **env)
// {
// 	char	**test;
// 	int		i;

// 	i = 0;
// 	test = ft_split("hello world test", ' ');
// 	while (test[i])
// 	{
// 		printf("%s\n", test[i]);
// 		i++;
// 	}
// 	ft_freee(test);
// 	i = 0;
// 	test = ft_split("hello world test", ' ');
// 	while (test[i])
// 	{
// 		printf("%s\n", test[i]);
// 		i++;
// 	}
// 	ft_freee(test);
// 	// int i;
// 	// int j;
// 	// char **str;

// 	// j = 0;
// 	// i = 0;
// 	// while (env[i])
// 	// 	i++;
// 	// while(j < i)
// 	// {
// 	// 	str = ft_split(env[j], '=');
// 	// 	// ft_addbottom(henv, str[0], str[1]);
// 	// 	ft_freee(str, ft_mots(env[j], '='));
// 	// 	// ft_freee(str, 3);
// 	// 	j++;
// 	// }
// }
#include "../minishell.h"

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

static	int	ft_mmots(char const *s, char c)
{
	int			i;
	int			k;
	int			p;
    int         d_q;

    d_q = 0;
	i = 0;
	k = 0;
	p = 1;
	if (*s)
	{
		while (s[i])
		{
			if (s[i] == '"')
			{
				i++;
				while (s[i] != '"')
					i++;
			}
			else if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
					i++;
			}
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

static int	ft_alphaa(char const *s, char c, int i)
{
	int	r;

	r = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'')
		{
			i++;
			// r++;
			while (s[i] && s[i] != '\'')
			{
				r++;
				i++;
			}
			// r++;
			i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
			{
				r++;
				i++;
			}
			i++;
		}
		else
		{
			r++;
			i++;
		}
	}
	return (r);
}

static char	**ft_rempp(char **p, char const *s, char c, int mots)
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
		p[j] = malloc(sizeof(char) * ft_alphaa(s, c, i) + 1);
		if (!p[j])
			return (ft_freee(p));
		while (s[i] && s[i] != c)
        {
			if (s[i] == '\'')
            {
				// p[j][k] = s[i];
                i++;
				// k++;
                while (s[i] != '\'')
                {
		        	p[j][k] = s[i];
					k++;
					i++;
                }
				// p[j][k] = s[i];
                i++;
				// k++;
            }
            else if (s[i] == '"')
            {
                i++;
                while (s[i] != '"')
                {
		        	p[j][k] = s[i];
					k++;
					i++;
                }
                i++;
            }
			else
				p[j][k++] = s[i++];
        }
		p[j][k] = '\0';
		j++;
	}
	p[j] = 0;
	return (p);
}

char	**ft_flex(char const *s, char c)
{
	char	**p;
	int		mots;

	if (s == NULL)
		return (0);
	mots = ft_mmots(s, c);
	p = malloc(sizeof(char *) * (mots + 1));
	if (!p)
		return (0);
	return (ft_rempp(p, s, c, mots));
}
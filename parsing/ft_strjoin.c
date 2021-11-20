#include "../minishell.h"

char	*ft_strjoin_dollar(char *s1, char *s2, int i)
{
	unsigned int		ss1;
	unsigned int		ss2;
	char				*new;

	ss1 = 0;
	ss2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[ss1] != '$')
		ss1++;
	while (s2[ss2] != '\0')
		ss2++;
	if (!(new = (char *)malloc((i + ss2 + 1) * sizeof(char))))
		return (0);
	ft_memmove(new, s1, i);
	ft_memmove(new + i, s2, ss2);
	new[i + ss2] = '\0';
	return (new);
}

char	*ft_strjoin_red(char *s1, char *s2, int i)
{
	unsigned int		ss2;
	char				*new;

	ss2 = 0;
	// printf("%s\n", s2);
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s2 && s2[ss2] != '\0')
		ss2++;
	if (!(new = (char *)malloc((i + ss2 + 1) * sizeof(char))))
		return (0);
	ft_memmove(new, s1, i);
	ft_memmove(new + i, s2, ss2);
	new[i + ss2] = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int		ss1;
	unsigned int		ss2;
	char				*new;

	ss1 = 0;
	ss2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[ss1] != '\0')
		ss1++;
	while (s2[ss2] != '\0')
		ss2++;
	if (!(new = (char *)malloc((ss1 + ss2 + 1) * sizeof(char))))
		return (0);
	ft_memmove(new, s1, ss1);
	ft_memmove(new + ss1, s2, ss2);
	new[ss1 + ss2] = '\0';
	return (new);
}

char *ft_strjoin_dollarfree(char *s1, char *s2, int i)
{
	char *ret;

	ret = ft_strjoin_dollar(s1, s2, i);
	free (s1);
	return (ret);
}

char *ft_strjoin_free(char *s1, char *s2)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	free (s1);
	return (ret);
}

char *ft_strjoin_free2(char *s1, char *s2)
{
	char *ret;

	ret = ft_strjoin(s1, s2);
	free (s2);
	return (ret);
}